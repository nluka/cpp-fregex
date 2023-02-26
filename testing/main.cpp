#include <iostream>

#include "../fregex.hpp"
#include "ntest.hpp"

namespace fs = std::filesystem;

int main() {
  ntest::init();

  ntest::assert_throws<std::runtime_error>([]() {
    fregex::find("does_not_exist", ".*");
  });
  ntest::assert_throws<std::runtime_error>([]() {
    fregex::find("", ".*");
  });
  ntest::assert_throws<std::runtime_error>([]() {
    fregex::find("files", "");
  });
  ntest::assert_throws<std::runtime_error>([]() {
    fregex::find("files", nullptr);
  });

  auto const sort = [](std::vector<fs::path> &files) {
    std::sort(
      files.begin(), files.end(),
      [](fs::path const &left, fs::path const &right) {
        return left > right;
      }
    );
  };

  {
    auto matches = fregex::find("files", ".*", true, "1.debug");
    std::vector<fs::path> expected {
      "files/python_book.md",
      "files/cpp_book.txt",
      "files/cBook.txt",
      "files/javaBook.txt",
      "files/javascriptBook.md",
      "files/child/advancedc.md",
      "files/child/advJava.txt",
      "files/child/advJavascript.md",
      "files/child/adv_cpp.txt",
      "files/child/adv_python.md",
    };
    sort(matches);
    sort(expected);
    ntest::assert_stdvec(expected, matches);
  }
  {
    auto matches = fregex::find("files", ".*", false, "2.debug");
    std::vector<fs::path> expected {
      // "files/child/advancedc.md",
      // "files/child/advJava.txt",
      // "files/child/advJavascript.md",
      // "files/child/adv_cpp.txt",
      // "files/child/adv_python.md",
      "files/cBook.txt",
      "files/cpp_book.txt",
      "files/javaBook.txt",
      "files/javascriptBook.md",
      "files/python_book.md",
    };
    sort(matches);
    sort(expected);
    ntest::assert_stdvec(expected, matches);
  }
  {
    auto matches = fregex::find("files", ".*\\.txt", true, "3.debug");
    std::vector<fs::path> expected {
      "files/cBook.txt",
      "files/cpp_book.txt",
      "files/javaBook.txt",
      "files/child/advJava.txt",
      "files/child/adv_cpp.txt",
    };
    sort(matches);
    sort(expected);
    ntest::assert_stdvec(expected, matches);
  }
  {
    auto matches = fregex::find("files", ".*\\.txt", false, "4.debug");
    std::vector<fs::path> expected {
      // "files/child/advJava.txt",
      // "files/child/adv_cpp.txt",
      "files/cBook.txt",
      "files/cpp_book.txt",
      "files/javaBook.txt",
    };
    sort(matches);
    sort(expected);
    ntest::assert_stdvec(expected, matches);
  }
  {
    auto matches = fregex::find("files", "python_.*", true, "5.debug");
    std::vector<fs::path> expected {
      "files/python_book.md",
    };
    sort(matches);
    sort(expected);
    ntest::assert_stdvec(expected, matches);
  }
  {
    auto matches = fregex::find("files", "java.*[bB]ook\\..*", true, "6.debug");
    std::vector<fs::path> expected {
      "files/javaBook.txt",
      "files/javascriptBook.md",
    };
    sort(matches);
    sort(expected);
    ntest::assert_stdvec(expected, matches);
  }
  {
    auto matches = fregex::find("files", "adv(anced)?_?[c](pp)?\\..*", true, "7.debug");
    std::vector<fs::path> expected {
      "files/child/advancedc.md",
      "files/child/adv_cpp.txt",
    };
    sort(matches);
    sort(expected);
    ntest::assert_stdvec(expected, matches);
  }

  auto const res = ntest::generate_report("fregex");
  std::cout << res.num_passes << " passed, " << res.num_fails << " failed\n";
}
