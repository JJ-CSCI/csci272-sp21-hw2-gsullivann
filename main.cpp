//------------------------------
//  DO NOT MODIFY NEXT LINE
//------------------------------
#include "catch.hpp"
//------------------------------

// Implement the class methods
class Rot13 {
  const int rotation{13};
  std::string text;
public:
  Rot13(std::string msg = "");
  void encrypt(std::string&, bool);

  bool operator!();
  void operator>>(std::string&);
  friend void operator<<(std::string&, Rot13&);
};

Rot13::Rot13(std::string msg){
//  for(int i=0; i<msg.length(); i++){
//    if (!(msg[i] == ' ' || (msg[i] >= 'a' && msg[i] <= 'z'))) {
//      text = " ";
//      return;
//    }
//  }
//  text = msg;
//}                 OR
  for (char c : msg) {
    if (!( c == ' ' || (c >= 'a' && c <= 'z'))) {
      text = " ";
      return;
    }
  }
  text = msg;
}

bool Rot13::operator!() {
  return text.empty();
}

void Rot13::encrypt(std::string& out, bool encrypt){
  int rot = (encrypt ? rotation : -rotation);
  for(char c : text) {
    if (c == ' ')
      out += c;
    else {
      int n = static_cast<int>(c);
      n += rot;
      if (n > 122)
        n = 26;
      if (n < 97)
        n += 26;        
      out += static_cast<char>(n);
    }
  }
}

void Rot13::operator>>(std::string& out){
  encrypt(out, true);
}

void operator<<(std::string& out, Rot13& cph){
  cph.encrypt(out, false);
}

//------------------------------
//   DO NOT MODIFY TEST CASES
//------------------------------
TEST_CASE( "Assignment" ) {
    SECTION( "v1" ) {
        Rot13 cipher;
        REQUIRE( !cipher );
    }
    SECTION( "v2" ) {
        Rot13 cipher{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
        REQUIRE( !cipher );
    }
    SECTION( "v3" ) {
        Rot13 cipher{"slkgjskjg  akjf Adkfjd fsdfj"};
        REQUIRE( !cipher );
    }
    SECTION( "v4" ) {
        Rot13 cipher{"abcdefghijkl mnopqrst uvwxyz"};
        REQUIRE( !!cipher );
    }
    SECTION( "e1" ) {
        Rot13 cipher{"abcdefghijkl mnopqrst uvwxyz"};
        REQUIRE( !!cipher );
        std::string secret;
        cipher >> secret;
        REQUIRE( secret == "nopqrstuvwxy zabcdefg hijklm" );
    }
    SECTION( "e2" ) {
        Rot13 cipher{"nopqrstuvwxy zabcdefg hijklm"};
        REQUIRE( !!cipher );
        std::string msg;
        msg << cipher;
        REQUIRE( msg == "abcdefghijkl mnopqrst uvwxyz" );
    }
}
//------------------------------
