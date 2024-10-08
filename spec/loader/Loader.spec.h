#ifndef __LOADER_SPEC_H_
#define __LOADER_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
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

  after({ remove("test.marg"); });
})

#endif
