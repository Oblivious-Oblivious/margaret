#ifndef __CLASSES_SPEC_H_
#define __CLASSES_SPEC_H_

#include "../_helpers.h"

module(classes_spec, {
    it("parses generating an object with inheritance", {
        parse("( \
            Point = Object subclass, \
            Point attr_reader: [\"x\", \"y\"], \
            \
            Point bind: #x: xparam y: yparam => ( \
                @x = xparam, \
                @y = yparam, \
                self \
            ), \
            \
            Point bind: #calc => @x + @y, \
            \
            Point multibind: [ \
                # + nil => self, \
                # + other => ( \
                    @x = @x + other x, \
                    @y = @y + other y, \
                    self \
                ) \
            ], \
            Point3D = Point subclass, \
            Point attr_reader: [\"z\"], \
            \
            Point3D bind: #x: x y: y z: z => ( \
                super x: @x y: @y, \
                @z = z, \
                self \
            ), \
            \
            Point3D bind: #calc => super calc + @z, \
            \
            Point3D bind: #+ other => ( \
                super + other, \
                @z = @z + other z, \
                self \
            ), \
            \
            p1 = Point3D x: 10 y: 20 z: 30, \
            p2 = Point3D x: 2 y: 4 z: 6, \
            \
            p1 calc puts, \
            p2 calc puts, \
            (p1 + p2 calc) puts \
        )", vector_new( \
            FM_LOCAL, string_new("Object"), \
            FM_UNARY, string_new("subclass"), \
            FM_STORE_LOCAL, string_new("Point"), \
            FM_LOCAL, string_new("Point"), \
            FM_STRING, string_new("x"), \
            FM_STRING, string_new("y"), \
            FM_TENSOR, string_new("2"), \
            FM_KEYWORD, string_new("attr_reader:"), string_new("1"), \
            FM_LOCAL, string_new("Point"), \
            FM_LOCAL, string_new("Method"), \
            FM_UNARY, string_new("keyword"), \
            FM_ANY_OBJECT, \
            FM_STRING, string_new("x:y:"), \
            FM_METHOD_PARAMETER, string_new("xparam"), \
            FM_METHOD_PARAMETER, string_new("yparam"), \
            FM_TENSOR, string_new("2"), \
            FM_START_PROC, \
                FM_PROC_PARAMETER, FM_SELF, \
                FM_PROC_PARAMETER, string_new("xparam"), \
                FM_PROC_PARAMETER, string_new("yparam"), \
                FM_LOCAL, string_new("xparam"), \
                FM_STORE_INSTANCE, string_new("x"), \
                FM_LOCAL, string_new("yparam"), \
                FM_STORE_INSTANCE, string_new("y"), \
                FM_SELF, \
            FM_END_PROC, \
            FM_KEYWORD, string_new("object:message:params:method:"), string_new("4"), \
            FM_KEYWORD, string_new("bind:"), string_new("1"), \
            FM_LOCAL, string_new("Point"), \
            FM_LOCAL, string_new("Method"), \
            FM_UNARY, string_new("unary"), \
            FM_ANY_OBJECT, \
            FM_STRING, string_new("calc"), \
            FM_START_PROC,
                FM_PROC_PARAMETER, FM_SELF, \
                FM_INSTANCE, string_new("x"), \
                FM_INSTANCE, string_new("y"), \
                FM_BINARY, string_new("+"), \
            FM_END_PROC, \
            FM_KEYWORD, string_new("object:message:method:"), string_new("3"), \
            FM_KEYWORD, string_new("bind:"), string_new("1"), \
            FM_LOCAL, string_new("Point"), \
            FM_LOCAL, string_new("Method"), \
            FM_UNARY, string_new("binary"), \
            FM_ANY_OBJECT, \
            FM_STRING, string_new("+"), \
            FM_NIL, \
            FM_START_PROC, \
                FM_PROC_PARAMETER, FM_SELF, \
                FM_SELF, \
            FM_END_PROC, \
            FM_KEYWORD, string_new("object:message:param:method:"), string_new("4"), \
            FM_LOCAL, string_new("Method"), \
            FM_UNARY, string_new("binary"), \
            FM_ANY_OBJECT, \
            FM_STRING, string_new("+"), \
            FM_METHOD_PARAMETER, string_new("other"), \
            FM_START_PROC, \
                FM_PROC_PARAMETER, FM_SELF, \
                FM_PROC_PARAMETER, string_new("other"), \
                FM_INSTANCE, string_new("x"), \
                FM_LOCAL, string_new("other"), \
                FM_UNARY, string_new("x"), \
                FM_BINARY, string_new("+"), \
                FM_STORE_INSTANCE, string_new("x"), \
                FM_INSTANCE, string_new("y"), \
                FM_LOCAL, string_new("other"), \
                FM_UNARY, string_new("y"), \
                FM_BINARY, string_new("+"), \
                FM_STORE_INSTANCE, string_new("y"), \
                FM_SELF, \
            FM_END_PROC, \
            FM_KEYWORD, string_new("object:message:param:method:"), string_new("4"), \
            FM_TENSOR, string_new("2"),
            FM_KEYWORD, string_new("multibind:"), string_new("1"), \
            FM_LOCAL, string_new("Point"), \
            FM_UNARY, string_new("subclass"), \
            FM_STORE_LOCAL, string_new("Point3D"), \
            FM_LOCAL, string_new("Point"), \
            FM_STRING, string_new("z"), \
            FM_TENSOR, string_new("1"), \
            FM_KEYWORD, string_new("attr_reader:"), string_new("1"), \
            FM_LOCAL, string_new("Point3D"), \
            FM_LOCAL, string_new("Method"), \
            FM_UNARY, string_new("keyword"), \
            FM_ANY_OBJECT, \
            FM_STRING, string_new("x:y:z:"), \
            FM_METHOD_PARAMETER, string_new("x"), \
            FM_METHOD_PARAMETER, string_new("y"), \
            FM_METHOD_PARAMETER, string_new("z"), \
            FM_TENSOR, string_new("3"), \
            FM_START_PROC, \
                FM_PROC_PARAMETER, FM_SELF, \
                FM_PROC_PARAMETER, string_new("x"), \
                FM_PROC_PARAMETER, string_new("y"), \
                FM_PROC_PARAMETER, string_new("z"), \
                FM_SUPER, \
                FM_INSTANCE, string_new("x"), \
                FM_INSTANCE, string_new("y"), \
                FM_KEYWORD, string_new("x:y:"), string_new("2"), \
                FM_LOCAL, string_new("z"), \
                FM_STORE_INSTANCE, string_new("z"), \
                FM_SELF, \
            FM_END_PROC, \
            FM_KEYWORD, string_new("object:message:params:method:"), string_new("4"), \
            FM_KEYWORD, string_new("bind:"), string_new("1"), \
            FM_LOCAL, string_new("Point3D"), \
            FM_LOCAL, string_new("Method"), \
            FM_UNARY, string_new("unary"), \
            FM_ANY_OBJECT, \
            FM_STRING, string_new("calc"), \
            FM_START_PROC,
                FM_PROC_PARAMETER, FM_SELF, \
                FM_SUPER, \
                FM_UNARY, string_new("calc"), \
                FM_INSTANCE, string_new("z"), \
                FM_BINARY, string_new("+"), \
            FM_END_PROC, \
            FM_KEYWORD, string_new("object:message:method:"), string_new("3"), \
            FM_KEYWORD, string_new("bind:"), string_new("1"), \
            FM_LOCAL, string_new("Point3D"), \
            FM_LOCAL, string_new("Method"), \
            FM_UNARY, string_new("binary"), \
            FM_ANY_OBJECT, \
            FM_STRING, string_new("+"), \
            FM_METHOD_PARAMETER, string_new("other"), \
            FM_START_PROC, \
                FM_PROC_PARAMETER, FM_SELF, \
                FM_PROC_PARAMETER, string_new("other"), \
                FM_SUPER, \
                FM_LOCAL, string_new("other"), \
                FM_BINARY, string_new("+"), \
                FM_INSTANCE, string_new("z"), \
                FM_LOCAL, string_new("other"), \
                FM_UNARY, string_new("z"), \
                FM_BINARY, string_new("+"), \
                FM_STORE_INSTANCE, string_new("z"), \
                FM_SELF, \
            FM_END_PROC, \
            FM_KEYWORD, string_new("object:message:param:method:"), string_new("4"), \
            FM_KEYWORD, string_new("bind:"), string_new("1"), \
            FM_LOCAL, string_new("Point3D"), \
            FM_INTEGER, string_new("10"), \
            FM_INTEGER, string_new("20"), \
            FM_INTEGER, string_new("30"), \
            FM_KEYWORD, string_new("x:y:z:"), string_new("3"), \
            FM_STORE_LOCAL, string_new("p1"), \
            FM_LOCAL, string_new("Point3D"), \
            FM_INTEGER, string_new("2"), \
            FM_INTEGER, string_new("4"), \
            FM_INTEGER, string_new("6"), \
            FM_KEYWORD, string_new("x:y:z:"), string_new("3"), \
            FM_STORE_LOCAL, string_new("p2"), \
            FM_LOCAL, string_new("p1"), \
            FM_UNARY, string_new("calc"), \
            FM_UNARY, string_new("puts"), \
            FM_LOCAL, string_new("p2"), \
            FM_UNARY, string_new("calc"), \
            FM_UNARY, string_new("puts"), \
            FM_LOCAL, string_new("p1"), \
            FM_LOCAL, string_new("p2"), \
            FM_UNARY, string_new("calc"), \
            FM_BINARY, string_new("+"), \
            FM_UNARY, string_new("puts") \
        ));
    });
})

#endif
