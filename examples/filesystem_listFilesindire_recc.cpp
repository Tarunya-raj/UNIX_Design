/*
    Reccursively traverse subdirectories
    1. take an input path
    2. check if its directory / regular file
    3. Check if valid permission are there to access
    4. If its directory list the leaf elemets(regular files)
    5. If internal elemets are directory call same function again to traverse
   the directory and list files.

    class directory_entry;
    object stores file attributes and file path.

    std::filesystem::directory_iterator iterates over directory elemets of a
   directory but does not visit subdirectories. special path . , .. are skipped.
    hidden files/ folders?

    directory entry behaves like ranges?

    std::filesystem::recursive_directory_iterator{dir name}
    iterates over the directory_entry elemts of a directory and recursively over
   the entries of all subdirectories. Iteration order not specified and each dir
   is visited only once. . .. skipped.



*/
#include <filesystem>
#include <iostream>

void listFiles(const std::filesystem::path& directoryPath) {
  // Iterate over std::filesystem::directory_entry elemetns
  for (const std::filesystem::directory_entry& dirEntry :
       std::filesystem::recursive_directory_iterator(directoryPath)) {
    std::cout << "\n Entry: " << dirEntry;
  }
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    throw "Enter valid directory path parameter\n";
    return -1;
  }
  std::filesystem::path dirPath = argv[1];
  try {
    listFiles(dirPath);
  } catch (const std::filesystem::filesystem_error& err) {
    std::cerr << "\nError: " << err.what();
  }
  return 0;
}
