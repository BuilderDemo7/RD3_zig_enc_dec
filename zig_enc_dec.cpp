#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

// Encryption and Decryption functions
void encrypt(const string &input_file, const string &output_file) {
	ifstream in_file(input_file, ios::binary);
	if (!in_file) {
		cerr << "Error opening input file for encryption." << endl;
		return;
	}

	// Read the entire input file into memory
	vector<unsigned char> data((istreambuf_iterator<char>(in_file)), istreambuf_iterator<char>());
	in_file.close();

	const string key = "This file is (C) Codemasters Software Company ltd. It took a lot of time and effort to produce. Leave it alone.";
	size_t key_length = key.length();
	size_t addnum = 7;  // Initial value of addnum
	size_t j = 0;  // Key index
	vector<unsigned char> output;

	// Encrypt the data byte by byte, mimicking the Lua script logic
	for (size_t i = 0; i < data.size(); i++) {
		unsigned char byte = data[i];  // Original byte
		unsigned char byte2 = key[j];  // Corresponding byte from key

		// First, reverse the first encryption operation: byte = (byte - addnum) % 256
		byte = (byte - addnum) % 256;  // Reverse the effect of adding addnum during encryption

		// Update addnum using the same logic as encryption
		addnum = (addnum * 0x5b) % 256;

		// Second, reverse the second encryption operation: byte = (byte - byte2) % 256
		byte = (byte - byte2) % 256;  // Reverse the effect of adding byte2 during encryption

		// Update the key index (move to the next byte in the key)
		j = (j + 1) % key_length;

		// Insert the encrypted byte into the output
		output.push_back(byte);
	}

	// Write the encrypted data to the output file
	ofstream out_file(output_file, ios::binary);
	if (!out_file) {
		cerr << "Error opening output file for encryption." << endl;
		return;
	}

	out_file.write(reinterpret_cast<const char*>(output.data()), output.size());
	out_file.close();
	cout << "File encrypted and saved as " << output_file << endl;
}

void decrypt(const string &input_file, const string &output_file) {
	ifstream in_file(input_file, ios::binary);
	if (!in_file) {
		cerr << "Error opening input file for decryption." << endl;
		return;
	}

	// Read the entire input file into memory
	vector<unsigned char> data((istreambuf_iterator<char>(in_file)), istreambuf_iterator<char>());
	in_file.close();

	const string key = "This file is (C) Codemasters Software Company ltd. It took a lot of time and effort to produce. Leave it alone.";
	size_t key_length = key.length();
	size_t addnum = 7;  // Initial value of addnum
	size_t j = 0;  // Key index
	vector<unsigned char> output;

	// Decrypt the data byte by byte, mimicking the Lua script logic
	for (size_t i = 0; i < data.size(); i++) {
		unsigned char byte = data[i];  // Encrypted byte
		unsigned char byte2 = key[j];  // Corresponding byte from key

		// Reverse the first operation: byte = (byte + byte2) % 256
		byte = (byte + byte2) % 256;  // Subtract byte2 to reverse encryption

		// Update the key index
		j = (j + 1) % key_length;

		// Reverse the second operation: byte = (byte + addnum) % 256
		byte = (byte + addnum) % 256;  // Subtract addnum to reverse encryption

		// Update addnum using the same logic as encryption
		addnum = (addnum * 0x5b) % 256;

		// Insert the decrypted byte into the output
		output.push_back(byte);
	}

	// Write the decrypted data to the output file
	ofstream out_file(output_file, ios::binary);
	if (!out_file) {
		cerr << "Error opening output file for decryption." << endl;
		return;
	}

	out_file.write(reinterpret_cast<const char*>(output.data()), output.size());
	out_file.close();
	cout << "File decrypted and saved as " << output_file << endl;
}

void print_usage() {
	cerr << "Usage: zig_enc_dec [-e|-d] input_file [-o output_file]" << endl;
	cerr << "  -e or -encrypt  : Encrypt the input file and save it as .big" << endl;
	cerr << "  -d or -decrypt  : Decrypt the input file and save it as .zig" << endl;
	cerr << "  -o output_file  : Optional. Specify the output file name. If not specified, the output file will have the same name as the input file with .big or .zig extension." << endl;
	cerr << "Example: zig_enc_dec -e input.big" << endl;
	cerr << "         zig_enc_dec -d input.zig" << endl;
	cerr << "         zig_enc_dec -e input.big -o output.zig" << endl;
}

int main(int argc, char* argv[]) {
	if (argc < 3) {
		print_usage();
		return 1;
	}

	string operation = argv[1];
	string input_file = argv[2];
	string output_file;

	// Check if output argument is provided
	if (argc == 5 && string(argv[3]) == "-o") {
		output_file = argv[4];
	}

	// Determine the output file if not provided
	if (output_file.empty()) {
		if (operation == "-e" || operation == "-encrypt") {
			output_file = input_file + ".big";  // Output encrypted file with .big extension
		}
		else if (operation == "-d" || operation == "-decrypt") {
			output_file = input_file + ".zig";  // Output decrypted file with .zig extension
		}
		else {
			print_usage();
			return 1;
		}
	}

	// Check if output file exists, and create it if not
	if (ifstream(output_file)) {
		cout << "Output file already exists, overwriting: " << output_file << endl;
	}
	else {
		cout << "Output file doesn't exist, creating: " << output_file << endl;
	}

	// Perform the operation based on the command line flag
	if (operation == "-e" || operation == "-encrypt") {
		encrypt(input_file, output_file);
	}
	else if (operation == "-d" || operation == "-decrypt") {
		decrypt(input_file, output_file);
	}
	else {
		print_usage();
		return 1;
	}

	return 0;
}
