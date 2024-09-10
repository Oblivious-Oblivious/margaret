#ifndef __LOADER_SPEC_H_
#define __LOADER_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/errors.h"
#include "../../src/loader/Loader.h"

module(LoaderSpec, {
  it("loads text character by character", {
    FILE *fd = fopen("test.marg", "w");
    fprintf(fd, "%s", "text");
    fclose(fd);

    VM *vm = vm_new("test.marg");
    loader_load(vm);
    assert_that(vm->error is NULL);

    assert_that_int(vm->source[0] equals to 't');
    assert_that_int(vm->source[1] equals to 'e');
    assert_that_int(vm->source[2] equals to 'x');
    assert_that_int(vm->source[3] equals to 't');
    assert_that_charptr(vm->source equals to "text");
  });

  it("does not load non-existing file", {
    VM *vm = vm_new("__this name does not exist__");
    loader_load(vm);
    assert_that_charptr(vm->error equals to ERROR_LOADER_FILE_NOT_FOUND);
    assert_that(vm->source is NULL);
  });

  after({ remove("test.marg"); });
})

#endif
