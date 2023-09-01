import subprocess
import shutil

def boot_uf2():
    command = [
        "fw\\esptool.exe",
        "--chip", "esp32s3",
        "--baud", "115200",
        "--before", "default_reset",
        "--after", "hard_reset",
        "write_flash",
        "-z",
        "--flash_mode", "dio",
        "--flash_freq", "80m",
        "--flash_size", "8MB",
        "0x0", "fw\\uf2.bootloader.bin",
        "0x8000", "fw\\uf2.partitions.bin",
        "0xe000", "fw\\ota_init.bin",
        "0x410000", "fw\\uf2.bin"
    ]
    subprocess.run(command)
    input("Press Enter to continue...")


def convert_uf2():
    # file_name = input("Please enter the name of the bin file to be converted: ")
    command = [
        "python",
        "fw\\uf2conv.py",
        "-b", "0x00",
        # f"{file_name}.bin",
        "..\\.pio\\build\\seeed_xiao_esp32s3\\firmware.bin",
        "-f", "ESP32S3",
        "-c",
        "-o", "firmware.uf2"
        # "-o", f"{file_name}.uf2"
    ]
    subprocess.run(command)

def copy_uf2_to_destination():
    source_file = "firmware.uf2"
    destination_directory = "path_to_the_directory"  # 替换为弹出文件夹的路径
    shutil.copy(source_file, destination_directory)


def main():
    while True:
        print("Please choose an option:")
        print("1. Run boot_uf2")
        print("2. Run convert_uf2")
        print("3. Quit")

        choice = input("> ")

        if choice == "1":
            boot_uf2()
        elif choice == "2":
            convert_uf2()
        elif choice == "3":
            break
        else:
            print("invalid option")

if __name__ == "__main__":
    main()
