#include "key_assassin.hpp"
#include <string>
#include <string_view>

// Conditional compilation for RE2
#ifdef USE_RE2
#include <re2/re2.h>
#endif

namespace ECE {

    // Static method: Takes string, returns clean string
    std::string KeyAssassin::Cleanse(std::string_view dirty_content) {
        std::string result(dirty_content); // Copy for modification

#ifdef USE_RE2
        // Optimized implementation using RE2
        // Order: Metadata, Artifacts, JSON Wrappers, Escapes

        // 1. Remove metadata patterns
        RE2 metadataPattern(R"raw("metadata"\s*:\s*\{[^}]*\},?\s*)raw");
        RE2::GlobalReplace(&result, metadataPattern, "");

        // 2. Remove common artifact patterns (longer matches first)
        RE2 artifactPattern(R"raw(\{(?:[^{}]*)?"response_content"\s*:\s*"([^"]*)"(?:[^}]*)?\})raw");
        RE2::GlobalReplace(&result, artifactPattern, "$1");

        // 3. Remove JSON wrapper patterns
        RE2 jsonWrapper(R"raw("response_content"\s*:\s*")([^"]*)(")raw");
        RE2::GlobalReplace(&result, jsonWrapper, "$1");

        // 4. Remove escaped quotes
        RE2 escapedQuotes(R"raw(\\")raw");
        RE2::GlobalReplace(&result, escapedQuotes, "\"");
#else
        // Fallback implementation using string operations
        // Order: Metadata, Artifacts, JSON Wrappers, Escapes
        size_t pos = 0;

        // 1. Remove common metadata patterns
        pos = 0;
        while ((pos = result.find("\"metadata\": {", pos)) != std::string::npos) {
            size_t start = pos;
            size_t end = result.find("},", start);
            if (end != std::string::npos) {
                result.erase(start, end - start + 2); // +2 for },
                pos = start;
            } else {
                pos += 13;
            }
        }

        // 2. Remove common artifact patterns (longer matches first)
        pos = 0;
        while ((pos = result.find("{\"response_content\": \"", pos)) != std::string::npos) {
            size_t start = pos;
            size_t contentStart = start + 22; // Length of "{\"response_content\": \""
            size_t end = result.find("\"}", contentStart);
            if (end != std::string::npos) {
                std::string content = result.substr(contentStart, end - contentStart);
                result.replace(start, end + 2 - start, content); // +2 for "}
                pos = start;
            } else {
                pos += 22;
            }
        }

        // 3. Remove common JSON wrapper patterns
        pos = 0;
        while ((pos = result.find("\"response_content\": \"", pos)) != std::string::npos) {
            size_t start = pos;
            size_t contentStart = start + 21; // Length of "\"response_content\": \""
            size_t end = result.find("\"", contentStart);
            if (end != std::string::npos) {
                std::string content = result.substr(contentStart, end - contentStart);
                result.replace(start, end + 1 - start, content); // +1 for closing quote
                pos = start;
            } else {
                pos += 21;
            }
        }

        // 4. Remove escaped quotes
        pos = 0;
        while ((pos = result.find("\\\"", pos)) != std::string::npos) {
            result.replace(pos, 2, "\"");
            pos += 1;
        }
#endif

        // Additional cleanup: remove leading/trailing whitespace and normalize
        size_t start = result.find_first_not_of(" \t\n\r");
        if (start == std::string::npos) {
            return ""; // string is all whitespace
        }
        size_t end = result.find_last_not_of(" \t\n\r");
        result = result.substr(start, end - start + 1);

        return result;
    }
}
