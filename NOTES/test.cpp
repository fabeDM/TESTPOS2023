#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "Note.hpp"

TEST_CASE("Creating note", "[Note]") {

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

}
