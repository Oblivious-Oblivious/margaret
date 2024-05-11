#ifndef __FILE_LOADER_SPEC_H_
#define __FILE_LOADER_SPEC_H_

#include "../../src/loader/file_loader.h"
#include "../../libs/cSpec/export/cSpec.h"

file_loader *loader;
void setup_file_loader(void) { loader = file_loader_new(); }

module(file_loader_spec, {
  before_each(&setup_file_loader);

  describe("File Loader", {
    it("creates a file_loader object", {
      file_loader *fl = file_loader_new();
      assert_that(fl isnot NULL);
    });

    context("on opening an existing file", {
      FILE *fd = fopen("new_file.txt", "w");

      it("reads file: `new_file.txt`", {
        int actual = file_loader_open(loader, "new_file.txt");
        assert_that(actual is true);
      });

      fclose(fd);
    });

    context("on opening an non existent file", {
      it("fails to read a file that is not yet created", {
        int actual = file_loader_open(loader, "this_filename_does_not_exist");
        assert_that(actual is false);
      });
    });

    context("on closing a file loader", {
      it("opens a file and successfully closes the buffer", {
        file_loader_open(loader, "new_file.txt");

        int actual = file_loader_close(loader);
        assert_that(actual is true);
      });
    });

    it("loads text character by character", {
      FILE *fd = fopen("test.marg", "w");
      fprintf(fd, "%s", "text");
      fclose(fd);

      string *text = file_loader_load(loader, "test.marg");
      assert_that_int(string_get_char_at_index(text, 0) equals to 't');
      assert_that_int(string_get_char_at_index(text, 1) equals to 'e');
      assert_that_int(string_get_char_at_index(text, 2) equals to 'x');
      assert_that_int(string_get_char_at_index(text, 3) equals to 't');
      assert_that_charptr(string_get(text) equals to "text");
    });
  });

  after({
    remove("new_file.txt");
    remove("test_file.txt");
    remove("test.marg");
  });
})

#endif
