import pathlib
import os

srcDir = "src/"
binDir = "binaries/"
txtDir = "txtFiles/"
directoryString = str(pathlib.Path(__file__).parent) + "\\"
directory = os.fsencode(directoryString)
sourceDirectory = os.fsencode(directoryString + srcDir)

try:
    os.mkdir(os.fsdecode(directory) + "/txtFiles")
except:
     print("Txt directory already exists")

try:
    os.mkdir(os.fsdecode(directory) + "/binaries")
except:
     print("Binary directory already exists")
     
for file in os.listdir(sourceDirectory):
    filename = srcDir + os.fsdecode(file)
    if filename.endswith(".e"): 
        zad = open(filename, "r", encoding = "utf-8")
        readLines = []
        word = [0, 0, 0, 0]
        flag = 0
        program = []
        comments = []
        newVersion = True

        while True:
            line = zad.readline()
            if not line:
                break
            readLines.append(line)

        for line in readLines:
            line_split = line.split()
            if len(line_split) > 3 and line_split[0][0] == "<" and line_split[1][0] != ";":
                if line_split[3] == ";":
                    newVersion = False
                    break;

        if newVersion:
            programToWrite = "logic [31:0] debug_memory [];\ninitial begin\ndebug_memory = new[];\n"
            bytes_location = {0: "7:0", 1: "15:8", 2: "23:16", 3: "31:24"}
            address = 0
            for line in readLines:
                line_split = line.split()
                try:
                    if len(line_split) < 2:
                        continue

                    if line_split[0][0] == "<" and line_split[1][0] != ";":
                        if line_split[1][-1] == "!":
                            line_split[1] = line_split[1][:-1]

                        try:
                            address = int(line_split[1], 16) // 4
                            offset = int(line_split[1], 16) % 4
                        except ValueError as ve:
                            print(f"Invalid address value: {line_split[1]} - {ve}")
                            continue

                        for string in line_split[2:6]:
                            if string[0] == ";":
                                break
                            if offset in bytes_location:
                                programToWrite += (
                                    f"debug_memory[{address}][{bytes_location[offset]}] = 8'h{string};\n"
                                )
                                offset += 1
                            else:
                                print(f"Invalid offset: {offset}")
                    elif line_split[0] == "|":
                        address += 1
                        if address > 1023:
                            raise ValueError(f"Address exceeds 1023: {address} in file {file_path.name}")
                        offset = 0
                        for string in line_split[1:]:
                            if offset in bytes_location:
                                programToWrite += (
                                    f"debug_memory[{address}][{bytes_location[offset]}] = 8'h{string};\n"
                                )
                                offset += 1
                            else:
                                print(f"Invalid offset: {offset}")
                except Exception as e:
                    print(f"Error processing line '{line}': {e}")
                    continue

            programToWrite += "end"
            programToWrite = programToWrite.replace("new[]", f"new[{address + 1}]")

            programFileDestination = open(txtDir + filename[4:-2] + ".txt", "w", encoding = "utf-8")
            programFileDestination.write(programToWrite)
            
        else:
            address = 0
            offset = 0
            bytes_location = {0: "7:0", 1: "15:8", 2: "23:16", 3: "31:24"}
            programToWrite = "logic [31:0] debug_memory [];\ninitial begin\ndebug_memory = new[];\n"
            for line in readLines:
                line_split = line.split()

                if len(line_split) > 0 and line_split[0][0] == "|":
                    programToWrite += f"debug_memory[{address}][{bytes_location[offset]}] = 8'h{line_split[1]};\n"
                    offset += 1
    
                elif len(line_split) > 1 and line_split[0][0] == "<" and line_split[1][0] != ";":
                    address = int(line_split[1], 16) // 4
                    offset = int(line_split[1], 16) % 4
                    programToWrite += f"debug_memory[{address}][{bytes_location[offset]}] = 8'h{line_split[2]};\n"
                    offset += 1

            programFileDestination = open(txtDir + filename[4:-2] + ".txt", "w", encoding = "utf-8")
            programToWrite += "end"
            programFileDestination.write(programToWrite)


        # for .b files
        if newVersion:    
            for line in readLines:
                line_split = line.split()
                try:
                    if len(line_split) < 2:
                        continue
                    if line_split[0][0] == "<" and line_split[1][0] != ";":
                        word[0] = str(line_split[5])
                        word[1] = str(line_split[4])
                        word[2] = str(line_split[3])
                        word[3] = str(line_split[2])
                        program.append("".join(word))
                except:
                    print("File", filename, "parsed.")
        else:            
            for line in readLines:
                line_split = line.split()
                try:
                    if len(line_split) < 2:
                        continue
                    if flag > 0:
                        flag = flag - 1
                        word[0 + flag] = str(line_split[1])
                        if flag == 0:
                            program.append("".join(word))
        
                    elif line_split[0][0] == "<" and line_split[1][0] != ";":
                        word[3] = str(line_split[2])
                        flag = 3
                except:
                    print("File", filename, "parsed.")

        binaryFileDestination = open(binDir + filename[4:-2] + ".b", "wb")
        counter = 0

        for line in program:
            binaryFileDestination.write(int(line, 16).to_bytes(4, byteorder='little'))
            counter += 1

        
    else:
        continue
