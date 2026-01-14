import threading
import serial
import time
import os

def readFileInBytes(path):
    read = b''
    with open(os.fsdecode(path), "rb") as file:
        while (byte := file.read(1)):
            read = read + byte
    return read

nule = "binaries/hrpaNuli.b"
procitaneNule = readFileInBytes(nule)

#serial port setup
connected = False
port = 'COM4'
baud = 115200
serial_port = serial.Serial(port, baud, timeout=0)

def handle_data(data):
    if len(data):
        try:
            print(data)
        except:
            print("error with uart byte")

def read_from_port(ser):
    print("[PYTHON]Async thread execution start")
    connected = False
    while not connected:
        connected = True

        while True:
            reading = ser.readline()
            handle_data(reading)

#an asynchronous thread that reads what it receives on the serial link
thread = threading.Thread(target=read_from_port, args=(serial_port,))
thread.start()

def reset():
    serial_port.write(b'1')
    print("[PYTHON]Reset!")

def run():
    serial_port.write(b'2') 
    print("[PYTHON]Run!")

def pause():
    serial_port.write(b'3')
    print("[PYTHON]Pause!")

def clearMem():
    serial_port.write(b'4')
    print("[PYTHON]Clear memory!")

def writeProgram(path):
    print("[PYTHON] Write program")

    program = readFileInBytes(path)
    program_size = len(program)
    # Send command
    serial_port.write(b'5')
    time.sleep(0.5)
    # Send size (u32 little endian)
    serial_port.write(program_size.to_bytes(4, byteorder='little'))
    time.sleep(0.5)
    # Send program bytes
    serial_port.write(program)
    time.sleep(0.5)

def writeData(addr1, addr2, putData):
    print("[PYTHON]Write data!")
    read = readFileInBytes(putData)
    serial_port.write(b'6')
    time.sleep(0.5)
    serial_port.write((b'0000' + str(addr1 >> 2).encode())[-4:])
    time.sleep(0.5)
    serial_port.write((b'0000' + str(addr2 >> 2).encode())[-4:])
    time.sleep(0.5)
    serial_port.write((read + procitaneNule)[:4096])

def readMem(addr1, addr2):
    print("[PYTHON]Read memory(range)!")
    serial_port.write(b'7')
    time.sleep(0.5)
    serial_port.write((b'0000' + str(addr1 >> 2).encode())[-4:])
    time.sleep(0.5)
    serial_port.write((b'0000' + str(addr2 >> 2).encode())[-4:])
    time.sleep(0.5)

def readMemSingle(addr):
    print("[PYTHON]Read memory(single)!")
    serial_port.write(b'8')
    time.sleep(0.1)
    serial_port.write((b'0000' + str(addr >> 2).encode())[-4:])
    time.sleep(0.1)

def parse(path):
    zad = open(path, "r", encoding = "utf-8")
    readLines = []
    word = [0, 0, 0, 0]
    flag = 0
    program = []
    comments = []

    while True:
        line = zad.readline()
        if not line:
            break
        readLines.append(line)

    for line in readLines:
        line_split = line.split()
        try:
            if flag > 0:
                flag = flag - 1
                word[0 + flag] = str(line_split[1])
                if flag == 0:
                    program.append("".join(word))
    
            elif line_split[0][0] == "<" and line_split[1][0] != ";":
                comments.append(" ".join(line_split[4:]))
                word[3] = str(line_split[2])
                flag = 3
        except:
            print("File", path, "parsed.")
    binaryFileDestination = open("binaries/parsed.b", "wb")
    counter = 0
    for line in program:
        binaryFileDestination.write(int(line, 16).to_bytes(4, byteorder='little'))
        counter += 1

def mainThread():
    print("[PYTHON]Main thread execution start")
    print("[PYTHON]Select option(type the number):")
    print("[PYTHON]    1 - Reset")
    print("[PYTHON]    2 - Run")
    print("[PYTHON]    3 - Pause")
    print("[PYTHON]    4 - Clear memory")
    print("[PYTHON]    5 - Write program")
    print("[PYTHON]    6 - Write data(addr1-addr2,data, format: hex, dec)")
    print("[PYTHON]    7 - Read Memory(addr1-addr2, format: hex, dec)")
    print("[PYTHON]    8 - Read Memory(addr, format: hex, dec)")
    print("[PYTHON]    9 - Debug function")
    print("[PYTHON]    0 - Exit")
    while 1:
        in_char = str(input(">>> "))
        if in_char == "1":
            reset()
        elif in_char == "2":
            run()
        elif in_char == "3":
            pause()
        elif in_char == "4":
            clearMem()
        elif in_char == "5":
            putProgram = input("[PYTHON]Write path to program:")
            writeProgram("binaries/" + putProgram + ".b")
        elif in_char == "6":
            form = input("[PYTHON]Write format(hex or dec):")
            addr1 = input("[PYTHON]Write addr1:")
            addr2 = input("[PYTHON]Write addr2:")
            if form == "hex":
                addr1 = int(addr1, 16)
                addr2 = int(addr2, 16)
            elif form == "dec":
                addr1 = int(addr1, 10)
                addr2 = int(addr2, 10)
            else:
                print("[PYTHON]Format is wrong")
                continue
            putData = input("[PYTHON]Write path to data file:")
            if addr2 < addr1 or addr2 > 4095 or addr1 < 0:
                print("[PYTHON]Addresses are wrong.")
                continue
            writeData(addr1, addr2, putData)
        elif in_char == "7":
            form = input("[PYTHON]Write format(hex or dec):")
            addr1 = input("[PYTHON]Write addr1:")
            addr2 = input("[PYTHON]Write addr2:")
            if form == "hex":
                addr1 = int(addr1, 16)
                addr2 = int(addr2, 16)
            elif form == "dec":
                addr1 = int(addr1, 10)
                addr2 = int(addr2, 10)
            else:
                print("[PYTHON]Format is wrong")
                continue
            if addr2 < addr1  or addr2 > 4095 or addr1 < 0:
                print("[PYTHON]Addresses are wrong.")
                continue
            readMem(addr1, addr2)
        elif in_char == "8":
            form = input("[PYTHON]Write format(hex or dec):")
            addr = input("[PYTHON]Write addr:")
            if form == "hex":
                addr = int(addr, 16)
            elif form == "dec":
                addr = int(addr, 10)
            else:
                print("[PYTHON]Format is wrong")
                continue
            if addr < 0:
                print("[PYTHON]Adrress is wrong")
                continue
            readMemSingle(addr)
        elif in_char == "9":
            serial_port.write(b'9')
        elif in_char == "0":
            os._exit(0)
        else:
            print("[PYTHON]Wrong input!")
#glavna dretva 
mainThread()
