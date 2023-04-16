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
        )", marg_vector_new( \
            FM_VARIABLE, marg_string_new("Object"), \
            FM_UNARY, marg_string_new("subclass"), \
            FM_STORE, marg_string_new("Point"), \
            FM_VARIABLE, marg_string_new("Point"), \
            FM_STRING, marg_string_new("x"), \
            FM_STRING, marg_string_new("y"), \
            FM_TENSOR, marg_string_new("2"), \
            FM_KEYWORD, marg_string_new("attr_reader:"), marg_string_new("1"), \
            FM_VARIABLE, marg_string_new("Point"), \
            FM_VARIABLE, marg_string_new("Method"), \
            FM_UNARY, marg_string_new("keyword"), \
            FM_ANY_OBJECT, \
            FM_STRING, marg_string_new("x:y:"), \
            FM_METHOD_PARAMETER, marg_string_new("xparam"), \
            FM_METHOD_PARAMETER, marg_string_new("yparam"), \
            FM_TENSOR, marg_string_new("2"), \
            FM_START_PROC, \
                FM_SELF, \
                FM_VARIABLE, marg_string_new("xparam"), \
                FM_VARIABLE, marg_string_new("yparam"), \
                FM_TENSOR, marg_string_new("3"), \
                FM_VARIABLE, marg_string_new("xparam"), \
                FM_STORE_INSTANCE, marg_string_new("x"), \
                FM_VARIABLE, marg_string_new("yparam"), \
                FM_STORE_INSTANCE, marg_string_new("y"), \
                FM_SELF, \
            FM_END_PROC, \
            FM_KEYWORD, marg_string_new("object:message:params:method:"), marg_string_new("4"), \
            FM_KEYWORD, marg_string_new("bind:"), marg_string_new("1"), \
            FM_VARIABLE, marg_string_new("Point"), \
            FM_VARIABLE, marg_string_new("Method"), \
            FM_UNARY, marg_string_new("unary"), \
            FM_ANY_OBJECT, \
            FM_STRING, marg_string_new("calc"), \
            FM_START_PROC,
                FM_SELF, \
                FM_TENSOR, marg_string_new("1"), \
                FM_INSTANCE, marg_string_new("x"), \
                FM_INSTANCE, marg_string_new("y"), \
                FM_BINARY, marg_string_new("+"), \
            FM_END_PROC, \
            FM_KEYWORD, marg_string_new("object:message:method:"), marg_string_new("3"), \
            FM_KEYWORD, marg_string_new("bind:"), marg_string_new("1"), \
            FM_VARIABLE, marg_string_new("Point"), \
            FM_VARIABLE, marg_string_new("Method"), \
            FM_UNARY, marg_string_new("binary"), \
            FM_ANY_OBJECT, \
            FM_STRING, marg_string_new("+"), \
            FM_NIL, \
            FM_START_PROC, \
                FM_SELF, \
                FM_TENSOR, marg_string_new("1"), \
                FM_SELF, \
            FM_END_PROC, \
            FM_KEYWORD, marg_string_new("object:message:param:method:"), marg_string_new("4"), \
            FM_VARIABLE, marg_string_new("Method"), \
            FM_UNARY, marg_string_new("binary"), \
            FM_ANY_OBJECT, \
            FM_STRING, marg_string_new("+"), \
            FM_METHOD_PARAMETER, marg_string_new("other"), \
            FM_START_PROC, \
                FM_SELF, \
                FM_VARIABLE, marg_string_new("other"), \
                FM_TENSOR, marg_string_new("2"), \
                FM_INSTANCE, marg_string_new("x"), \
                FM_VARIABLE, marg_string_new("other"), \
                FM_UNARY, marg_string_new("x"), \
                FM_BINARY, marg_string_new("+"), \
                FM_STORE_INSTANCE, marg_string_new("x"), \
                FM_INSTANCE, marg_string_new("y"), \
                FM_VARIABLE, marg_string_new("other"), \
                FM_UNARY, marg_string_new("y"), \
                FM_BINARY, marg_string_new("+"), \
                FM_STORE_INSTANCE, marg_string_new("y"), \
                FM_SELF, \
            FM_END_PROC, \
            FM_KEYWORD, marg_string_new("object:message:param:method:"), marg_string_new("4"), \
            FM_TENSOR, marg_string_new("2"),
            FM_KEYWORD, marg_string_new("multibind:"), marg_string_new("1"), \
            FM_VARIABLE, marg_string_new("Point"), \
            FM_UNARY, marg_string_new("subclass"), \
            FM_STORE, marg_string_new("Point3D"), \
            FM_VARIABLE, marg_string_new("Point"), \
            FM_STRING, marg_string_new("z"), \
            FM_TENSOR, marg_string_new("1"), \
            FM_KEYWORD, marg_string_new("attr_reader:"), marg_string_new("1"), \
            FM_VARIABLE, marg_string_new("Point3D"), \
            FM_VARIABLE, marg_string_new("Method"), \
            FM_UNARY, marg_string_new("keyword"), \
            FM_ANY_OBJECT, \
            FM_STRING, marg_string_new("x:y:z:"), \
            FM_METHOD_PARAMETER, marg_string_new("x"), \
            FM_METHOD_PARAMETER, marg_string_new("y"), \
            FM_METHOD_PARAMETER, marg_string_new("z"), \
            FM_TENSOR, marg_string_new("3"), \
            FM_START_PROC, \
                FM_SELF, \
                FM_VARIABLE, marg_string_new("x"), \
                FM_VARIABLE, marg_string_new("y"), \
                FM_VARIABLE, marg_string_new("z"), \
                FM_TENSOR, marg_string_new("4"), \
                FM_SUPER, \
                FM_INSTANCE, marg_string_new("x"), \
                FM_INSTANCE, marg_string_new("y"), \
                FM_KEYWORD, marg_string_new("x:y:"), marg_string_new("2"), \
                FM_VARIABLE, marg_string_new("z"), \
                FM_STORE_INSTANCE, marg_string_new("z"), \
                FM_SELF, \
            FM_END_PROC, \
            FM_KEYWORD, marg_string_new("object:message:params:method:"), marg_string_new("4"), \
            FM_KEYWORD, marg_string_new("bind:"), marg_string_new("1"), \
            FM_VARIABLE, marg_string_new("Point3D"), \
            FM_VARIABLE, marg_string_new("Method"), \
            FM_UNARY, marg_string_new("unary"), \
            FM_ANY_OBJECT, \
            FM_STRING, marg_string_new("calc"), \
            FM_START_PROC,
                FM_SELF, \
                FM_TENSOR, marg_string_new("1"), \
                FM_SUPER, \
                FM_UNARY, marg_string_new("calc"), \
                FM_INSTANCE, marg_string_new("z"), \
                FM_BINARY, marg_string_new("+"), \
            FM_END_PROC, \
            FM_KEYWORD, marg_string_new("object:message:method:"), marg_string_new("3"), \
            FM_KEYWORD, marg_string_new("bind:"), marg_string_new("1"), \
            FM_VARIABLE, marg_string_new("Point3D"), \
            FM_VARIABLE, marg_string_new("Method"), \
            FM_UNARY, marg_string_new("binary"), \
            FM_ANY_OBJECT, \
            FM_STRING, marg_string_new("+"), \
            FM_METHOD_PARAMETER, marg_string_new("other"), \
            FM_START_PROC, \
                FM_SELF, \
                FM_VARIABLE, marg_string_new("other"), \
                FM_TENSOR, marg_string_new("2"), \
                FM_SUPER, \
                FM_VARIABLE, marg_string_new("other"), \
                FM_BINARY, marg_string_new("+"), \
                FM_INSTANCE, marg_string_new("z"), \
                FM_VARIABLE, marg_string_new("other"), \
                FM_UNARY, marg_string_new("z"), \
                FM_BINARY, marg_string_new("+"), \
                FM_STORE_INSTANCE, marg_string_new("z"), \
                FM_SELF, \
            FM_END_PROC, \
            FM_KEYWORD, marg_string_new("object:message:param:method:"), marg_string_new("4"), \
            FM_KEYWORD, marg_string_new("bind:"), marg_string_new("1"), \
            FM_VARIABLE, marg_string_new("Point3D"), \
            FM_INTEGER, marg_string_new("10"), \
            FM_INTEGER, marg_string_new("20"), \
            FM_INTEGER, marg_string_new("30"), \
            FM_KEYWORD, marg_string_new("x:y:z:"), marg_string_new("3"), \
            FM_STORE, marg_string_new("p1"), \
            FM_VARIABLE, marg_string_new("Point3D"), \
            FM_2, \
            FM_INTEGER, marg_string_new("4"), \
            FM_INTEGER, marg_string_new("6"), \
            FM_KEYWORD, marg_string_new("x:y:z:"), marg_string_new("3"), \
            FM_STORE, marg_string_new("p2"), \
            FM_VARIABLE, marg_string_new("p1"), \
            FM_UNARY, marg_string_new("calc"), \
            FM_UNARY, marg_string_new("puts"), \
            FM_VARIABLE, marg_string_new("p2"), \
            FM_UNARY, marg_string_new("calc"), \
            FM_UNARY, marg_string_new("puts"), \
            FM_VARIABLE, marg_string_new("p1"), \
            FM_VARIABLE, marg_string_new("p2"), \
            FM_UNARY, marg_string_new("calc"), \
            FM_BINARY, marg_string_new("+"), \
            FM_UNARY, marg_string_new("puts") \
        ));
    });
})

#endif
