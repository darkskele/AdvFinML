from sqlalchemy import Column, Integer, Float, BigInteger
from sqlalchemy.orm import DeclarativeBase

class Base(DeclarativeBase):
    pass

# Data from binance
class BTCUSDT_Kline_1s(Base):
    __tablename__ = 'btcusdt_kline_1s'

    open_time = Column(BigInteger, primary_key=True)  # ms timestamp
    open = Column(Float)
    high = Column(Float)
    low = Column(Float)
    close = Column(Float)
    volume = Column(Float)
    close_time = Column(BigInteger)
    quote_volume = Column(Float)
    num_trades = Column(Integer)
    taker_buy_base_volume = Column(Float)
    taker_buy_quote_volume = Column(Float)
    ignore = Column(Integer)  # always 0