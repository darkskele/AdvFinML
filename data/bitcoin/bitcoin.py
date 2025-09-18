import os
import csv
import zipfile
import requests
from tqdm import tqdm
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
from models import BTCUSDT_TradeTick, Base 

# Define data paths
DATA_DIR = "data/bitcoin"
DB_PATH = os.path.join(DATA_DIR, "bitcoin.db")
DB_URI = f"sqlite:///{DB_PATH}"
BASE_URL = "https://data.binance.vision/data/spot/daily/trades/BTCUSDT/"

# Database setup
engine = create_engine(DB_URI)
Base.metadata.create_all(engine)
Session = sessionmaker(bind=engine)
session = Session()

# Download data
def download_zip(day: int, month: int = 5, year: int = 2025) -> str:
    # Constructing paths
    filename = f"BTCUSDT-trades-{year}-{month:02d}-{day:02d}"
    zip_path = os.path.join(DATA_DIR, f"{filename}.zip")
    url = f"{BASE_URL}{filename}.zip"

    print(f"Downloading {filename}...")

    # Setup request
    r = requests.get(url)
    if r.status_code == 200:
        # Right received content to zip
        with open(zip_path, "wb") as f:
            f.write(r.content)
        # Extract zip
        with zipfile.ZipFile(zip_path, "r") as zip_ref:
            zip_ref.extractall(DATA_DIR)
    else:
        print(f"Failed to download {filename} : {r.status_code}")

    return f"{filename}.csv"

# Parse into SQL table
def parse_csv_and_insert(csv_file: str):
    # Open CSV
    with open(csv_file, "r") as f:
        # Get reader
        reader = csv.reader(f)
        # Parse each row
        for row in reader:
            try:
                tick = BTCUSDT_TradeTick(
                    trade_id=int(row[0]),
                    price=float(row[1]),
                    qty=float(row[2]),
                    quote_qty=float(row[3]),
                    timestamp=int(float(row[4])),  # sometimes it's in scientific notation
                    is_buyer_maker=row[5].lower() == 'true',
                    is_best_match=row[6].lower() == 'true'
                )
                session.add(tick)
            except Exception as ex:
                print(f"Skipping row due to error: {ex}")
    session.commit()

# Clean up
def clean_up(file_path: str):
    zip_path = file_path.replace(".csv", ".zip")
    os.remove(file_path)
    if os.path.exists(zip_path):
        os.remove(zip_path)


def main():
    # Make data dir
    os.makedirs(DATA_DIR, exist_ok=True)

    # Download and process a range of days
    for day in tqdm(range(1, 29)):
        file = os.path.join(DATA_DIR, download_zip(day))
        parse_csv_and_insert(file)
        clean_up(file)

    session.close()

if __name__ == "__main__":
    main()