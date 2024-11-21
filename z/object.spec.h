#ifndef __OBJECT_SPEC_H_
#define __OBJECT_SPEC_H_

#include "../libs/cSpec/export/cSpec.h"
#include "../libs/EmeraldsString/export/EmeraldsString.h"
#include "helpers.spec.h"
#include "instruction.h"
#include "nan_tagging.h"

module(object_spec, {
  before_each(&reset_vm);

  it("ensures cloned objects do not receive label values from parent", {
    MargValue marg = G("$Margaret");
    assert_that(marg isnot MARG_UNDEFINED);
    assert_that_charptr(AS_OBJECT(marg)->name equals to "$Margaret");
    assert_that_size_t(AS_OBJECT(marg)->name_hash equals to 4789181502764186150
    );
    table_add(
      &AS_OBJECT(marg)->instance_variables, "@::l1", MARG_LABEL("@::l1")
    );
    table_add(
      &AS_OBJECT(marg)->instance_variables, "@::l2", MARG_LABEL("@::l2")
    );

    assert_that_size_t(table_size(&AS_OBJECT(marg)->instance_variables)
                         equals to 4);

    MargValue clone = SG(marg, "ACLONE");
    assert_that(clone isnot MARG_UNDEFINED);
    assert_that_charptr(AS_OBJECT(clone)->name equals to "ACLONE");
    assert_that_charptr(AS_OBJECT(clone)->proto->name equals to "$Margaret");
    assert_that_size_t(AS_OBJECT(clone)->name_hash equals to 3455395588760667778
    );
    assert_that_size_t(
      AS_OBJECT(clone)->proto->name_hash equals to 4789181502764186150
    );
    assert_that_size_t(table_size(&AS_OBJECT(clone)->instance_variables)
                         equals to 2);
  });

  it("ensures @self and @super are setup correctly", {
    MargValue clone = SG(G("$Margaret"), "ACLONE");

    assert_that_charptr(AS_OBJECT(AS_OBJECT(clone)->instance_registers[0])
                          ->name equals to "ACLONE");
    assert_that_charptr(AS_OBJECT(AS_OBJECT(clone)->instance_registers[1])
                          ->name equals to "$Margaret");
    assert_that_size_t(AS_OBJECT(AS_OBJECT(clone)->instance_registers[0])
                         ->name_hash equals to 3455395588760667778);
    assert_that_size_t(AS_OBJECT(AS_OBJECT(clone)->instance_registers[1])
                         ->name_hash equals to 4789181502764186150);
  });
})

#endif
