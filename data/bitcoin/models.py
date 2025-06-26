from sqlalchemy import Column, Boolean, Float, BigInteger
from sqlalchemy.orm import DeclarativeBase

class Base(DeclarativeBase):
    pass

class BTCUSDT_TradeTick(Base):
    __tablename__ = 'btcusdt_trade_ticks'

    trade_id = Column(BigInteger, primary_key=True)        # Unique trade ID
    price = Column(Float, nullable=False)                  # Trade price
    qty = Column(Float, nullable=False)                    # Base asset quantity
    quote_qty = Column(Float, nullable=False)              # Quote asset volume (price * qty)
    timestamp = Column(BigInteger, nullable=False)         # Millisecond timestamp
    is_buyer_maker = Column(Boolean, nullable=False)       # True if buyer is maker
    is_best_match = Column(Boolean, nullable=False)        # Always True (per Binance)