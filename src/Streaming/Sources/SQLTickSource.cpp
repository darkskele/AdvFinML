#include "SQLTickSource.hpp"

#include <stdexcept>

namespace Streaming
{
    SQLTickSource::SQLTickSource(const std::string &db_path)
    {
        // Connect to database
        if (sqlite3_open(db_path.c_str(), &db_) != SQLITE_OK)
        {
            throw std::runtime_error("Failed to open DB: " + db_path);
        }

        // Prepare statement
        const char *query = R"SQL(
            SELECT trade_id, price, qty, quote_qty, timestamp, is_buyer_maker, is_best_match
            FROM BTCUSDT_TradeTick
            ORDER BY timestamp ASC 
        )SQL";

        // Prepare
        if (sqlite3_prepare_v2(db_, query, -1, &stmt_, nullptr) != SQLITE_OK)
        {
            throw std::runtime_error("Failed to prepare statement!");
        }
    }

    SQLTickSource::~SQLTickSource()
    {
        // Finalise and close
        if (stmt_)
            sqlite3_finalize(stmt_);
        if (db_)
            sqlite3_close(db_);
    }

    std::optional<FinDS::TradeTick> SQLTickSource::next()
    {
        // Query until no more rows
        if (sqlite3_step(stmt_) != SQLITE_ROW)
        {
            // End of table
            return std::nullopt;
        }

        // Format tick
        return FinDS::TradeTick
        {
            .trade_id = sqlite3_column_int64(stmt_, 0),
            .price = sqlite3_column_double(stmt_, 1),
            .qty = sqlite3_column_double(stmt_, 2),
            .quote_qty = sqlite3_column_double(stmt_, 3),
            .timestamp_ms = sqlite3_column_int64(stmt_, 4),
            .is_buyer_match = static_cast<bool>(sqlite3_column_int(stmt_, 5)),
            .is_best_match = static_cast<bool>(sqlite3_column_int(stmt_, 6)),
        };
    }

}