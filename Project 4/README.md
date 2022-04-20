# Programming Project 3
The goal of this project was to expand on Project 2 by adding Error Detection and Correction using Cyclic Redundancy Checker (CRC) and Hamming.

At execution time, the use of CRC or Hamming is decided with a command line argument.

The CRC Checksum of a dataframe was calculated and appended to a dataframe by the Producer before it was sent to the Consumer. The Consumer calculates the CRC Checksum of the received frame and compares it to the value appended to the frame by the Producer. If the values match, no error was detected. If the values differ, an error was detected within that specific frame.

The Hamming Code was computed using the standard Hamming code algorithm. The calculation allows the Consumer to perform single-bit error correction by checking parity bits of the data sent.
