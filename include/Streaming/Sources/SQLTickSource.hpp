#pragma once

#include <sqlite3.h>
#include <string>
#include <optional>

#include "TradeTick.hpp"

namespace Streaming
{
    /**
     * @brief Provides an iterator-style interface for reading TradeTicks from an SQLite database.
     * 
     * This class prepares and steps through a SQL result set, exposing each row as a `TradeTick`.
     */
    class SQLTickSource
    {
    public:
        /**
         * @brief Constructs a SQLTickSource and opens the SQLite database at the given path.
         * 
         * @param db_path Path to the SQLite database file containing trade tick data.
         * 
         * @throws std::runtime_error if the database cannot be opened or the query cannot be prepared.
         */
        explicit SQLTickSource(const std::string &db_path);

        /**
         * @brief Closes the database connection and finalizes the prepared statement.
         */
        ~SQLTickSource();

        /**
         * @brief Reads the next row from the database and returns it as a TradeTick.
         * 
         * @return std::optional<FinDS::TradeTick> The next TradeTick, or std::nullopt if no more rows are available.
         */
        std::optional<FinDS::TradeTick> next();

    private:
        sqlite3 *db_ = nullptr;     ///< SQLite database handle.
        sqlite3_stmt *stmt_ = nullptr; ///< Prepared statement for tick iteration.
    };
}
