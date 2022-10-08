#ifndef __FILE_LOADER_SPEC_H_
#define __FILE_LOADER_SPEC_H_

#include "../../src/lexer/FileLoader.h"
#include "../cSpec.h"

FileLoader *file_loader;
void setup_file_loader(void) {
    file_loader = file_loader_new();
}

module(FileLoaderSpec, {
    before_each(&setup_file_loader);

    describe("File Loader", {
        it("creates a FileLoader object", {
            FileLoader *fl = file_loader_new();
            assert_that(fl isnot NULL);
        });

        context("on opening an existing file", {
            FILE *fd = fopen("new_file.txt", "w");

            it("reads file: `new_file.txt`", {
                int actual = file_loader_open(file_loader, "new_file.txt");
                assert_that(actual is true);
            });

            fclose(fd);
        });

        context("on opening an non existent file", {
            it("fails to read a file that is not yet created", {
                int actual = file_loader_open(file_loader, "this_filename_does_not_exist");
                assert_that(actual is false);
            });
        });

        context("on closing a file loader", {
            it("opens a file and successfully closes the buffer", {
                file_loader_open(file_loader, "new_file.txt");

                int actual = file_loader_close(file_loader);
                assert_that(actual is true);
            });
        });

        it("loads text character by character", {
            FILE *fd = fopen("test.marg", "w");
            fprintf(fd, "%s", "text");
            fclose(fd);

            marg_string *text = file_loader_load(file_loader, "test.marg");
            assert_that_int(marg_string_get_char_at_index(text, 0) equals to 't');
            assert_that_int(marg_string_get_char_at_index(text, 1) equals to 'e');
            assert_that_int(marg_string_get_char_at_index(text, 2) equals to 'x');
            assert_that_int(marg_string_get_char_at_index(text, 3) equals to 't');
            assert_that_charptr(marg_string_get(text) equals to "text");
        });
    });

    after({
        remove("new_file.txt");
        remove("test_file.txt");
        remove("test.marg");
    });
})

#endif
