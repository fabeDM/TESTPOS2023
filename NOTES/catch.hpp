#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "Note.hpp"  // Include the necessary header files for your tests

TEST_CASE("Note creation", "[Note]") {
    // Write your test cases here using Catch2 syntax
    SECTION("Default constructor creates empty note") {
        Note note;
        REQUIRE(note.getTitle().empty());
        REQUIRE(note.getContent().empty());
    }

    SECTION("Constructor sets title and content") {
        Note note("Title", "Content");
        REQUIRE(note.getTitle() == "Title");
        REQUIRE(note.getContent() == "Content");
    }

    // Add more test cases as needed
}
