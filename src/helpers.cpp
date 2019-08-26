#include <Rcpp.h>
using namespace Rcpp;

//' Flexibly (big/little endian, signed/unsigned) convert two raw bytes to short
//'
//' @param x the bytes (RawVector) from which to extract the short
//' @param i1 integer. The index of the first byte
//' @param i2 integer. The index of the second byte
//' @param is_signed boolean. Return a signed value?
//'
//' @keywords internal
// [[Rcpp::export]]
int get_short(RawVector x, int i1, int i2, bool is_signed) {
  if (is_signed) {
    short value = x[i1] << 8 | x[i2];
    return value;
  } else {
    unsigned short value = (unsigned short)(
      x[i1] << 8 | x[i2]
    );
    return value;
  }
}

//' Print progress updates while parsing packets in C++
//'
//' @param n percentage progress
//' @param label the packet type, as character
//'
//' @keywords internal
// [[Rcpp::export]]
void print_progC(int n, const char* label) {

  Rcout << "  Parsing " << label <<
  " packet(s)   ............. " <<
  n << "%";

}

//' Calculate checksum for a packet in C++
//'
//' @param log RawVector representing the contents of log.bin
//' @param start_index the packet start index
//' @param end_index the packet end index
//'
//' @keywords internal
// [[Rcpp::export]]
void checksumC(RawVector log, int start_index, int end_index) {

  unsigned char checksum(0xFF);
  for (int i = start_index; i < end_index; ++i) {
    checksum ^= log[i];
  }

  bool pass = checksum == log[end_index];
  if (!pass) {
    stop("Cheksum calculation failed.");
  }

}