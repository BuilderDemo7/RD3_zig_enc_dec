# ToCA Race Driver 3 ZIG Encrypter & Decrypter
This tool allows you to modify the car engine sound effects of ToCA Race Driver 3 based on a [QuickBMS script](https://aluigi.altervista.org/bms/rdzig2big.bms)                                                         
# Usage
This is a console command program so to use it you will most likely need a .bat file or a shortcut with specified parameters.                                                                 
- Usage: zig_enc_dec [-e|-d] input_file [-o output_file]                                                                        
Use -d(ecrypt) for decrypting .zig files and use -e(ncrypt) for making new .zig files from a .big file (it will be written to the output file by the parameter -o)                                                                          
## Examples
- Decrypting: zig_enc_dec -d myZigFile.zig
- Decrypting (full): zig_enc_dec -decrypt zigfile.zig -o zigfile_output.big
- Encrypting: zig_enc_dec -e myZigFile.big
- Encrypting (full): zig_enc_dec -encrypt zigfile.big -o zigfile_modded.zig
# New Car Sounds
You will need a program that can open .big files [(you can find iRipper 1.9 here)](https://sites.google.com/view/toca-rdsport/Utilities), to generate the .big files from .zig files see [Usage](https://github.com/BuilderDemo7/RD3_zig_enc_dec?tab=readme-ov-file#usage).                                     
# Releases / Download
You can get all the releases [here](https://github.com/BuilderDemo7/RD3_zig_enc_dec/releases).                
But the latest release is [this](https://github.com/BuilderDemo7/RD3_zig_enc_dec/releases/latest).    