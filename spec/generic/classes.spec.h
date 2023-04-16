#ifndef __CLASSES_SPEC_H_
#define __CLASSES_SPEC_H_

#include "../_helpers.h"

module(classes_spec, {
    it("parses generating an object with inheritance", {
        parse("( \
            Point = Object subclass, \
            Point attr_reader: [\"x\", \"y\"], \
            \
            Point message: #x: xparam y: yparam => ( \
                @x = xparam, \
                @y = yparam, \
                self \
            ), \
            \
            Point message: #calc => @x + @y, \
            \
            Point message: #+ other => ( \
                @x = @x + other x, \
                @y = @y + other y, \
                self \
            ), \
            \
            Point3D = Point subclass, \
            Point attr_reader: [\"z\"], \
            \
            Point3D message: #x: x y: y z: z => ( \
                super x: @x y: @y, \
                @z = z, \
                self \
            ), \
            \
            Point3D message: #calc => super calc + @z, \
            \
            Point3D message: #+ other => ( \
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
            OP_VARIABLE, marg_string_new("Object"), \
            OP_UNARY, marg_string_new("subclass"), \
            OP_STORE, marg_string_new("Point"), \
            OP_VARIABLE, marg_string_new("Point"), \
            OP_STRING, marg_string_new("x"), \
            OP_STRING, marg_string_new("y"), \
            OP_TENSOR, marg_string_new("2"), \
            OP_KEYWORD, marg_string_new("attr_reader:"), marg_string_new("1"), \
            OP_VARIABLE, marg_string_new("Point"), \
            OP_VARIABLE, marg_string_new("Method"), \
            OP_UNARY, marg_string_new("keyword"), \
            OP_ANY_OBJECT, \
            OP_STRING, marg_string_new("x:y:"), \
            OP_METHOD_PARAMETER, marg_string_new("xparam"), \
            OP_METHOD_PARAMETER, marg_string_new("yparam"), \
            OP_TENSOR, marg_string_new("2"), \
            OP_START_PROC, \
                OP_SELF, \
                OP_VARIABLE, marg_string_new("xparam"), \
                OP_VARIABLE, marg_string_new("yparam"), \
                OP_TENSOR, marg_string_new("3"), \
                OP_VARIABLE, marg_string_new("xparam"), \
                OP_STORE_INSTANCE, marg_string_new("x"), \
                OP_VARIABLE, marg_string_new("yparam"), \
                OP_STORE_INSTANCE, marg_string_new("y"), \
                OP_SELF, \
            OP_END_PROC, \
            OP_KEYWORD, marg_string_new("object:message:params:method:"), marg_string_new("4"), \
            OP_KEYWORD, marg_string_new("message:"), marg_string_new("1"), \
            OP_VARIABLE, marg_string_new("Point"), \
            OP_VARIABLE, marg_string_new("Method"), \
            OP_UNARY, marg_string_new("unary"), \
            OP_ANY_OBJECT, \
            OP_STRING, marg_string_new("calc"), \
            OP_START_PROC,
                OP_SELF, \
                OP_TENSOR, marg_string_new("1"), \
                OP_INSTANCE, marg_string_new("x"), \
                OP_INSTANCE, marg_string_new("y"), \
                OP_BINARY, marg_string_new("+"), \
            OP_END_PROC, \
            OP_KEYWORD, marg_string_new("object:message:method:"), marg_string_new("3"), \
            OP_KEYWORD, marg_string_new("message:"), marg_string_new("1"), \
            OP_VARIABLE, marg_string_new("Point"), \
            OP_VARIABLE, marg_string_new("Method"), \
            OP_UNARY, marg_string_new("binary"), \
            OP_ANY_OBJECT, \
            OP_STRING, marg_string_new("+"), \
            OP_METHOD_PARAMETER, marg_string_new("other"), \
            OP_START_PROC, \
                OP_SELF, \
                OP_VARIABLE, marg_string_new("other"), \
                OP_TENSOR, marg_string_new("2"), \
                OP_INSTANCE, marg_string_new("x"), \
                OP_VARIABLE, marg_string_new("other"), \
                OP_UNARY, marg_string_new("x"), \
                OP_BINARY, marg_string_new("+"), \
                OP_STORE_INSTANCE, marg_string_new("x"), \
                OP_INSTANCE, marg_string_new("y"), \
                OP_VARIABLE, marg_string_new("other"), \
                OP_UNARY, marg_string_new("y"), \
                OP_BINARY, marg_string_new("+"), \
                OP_STORE_INSTANCE, marg_string_new("y"), \
                OP_SELF, \
            OP_END_PROC, \
            OP_KEYWORD, marg_string_new("object:message:param:method:"), marg_string_new("4"), \
            OP_KEYWORD, marg_string_new("message:"), marg_string_new("1"), \
            OP_VARIABLE, marg_string_new("Point"), \
            OP_UNARY, marg_string_new("subclass"), \
            OP_STORE, marg_string_new("Point3D"), \
            OP_VARIABLE, marg_string_new("Point"), \
            OP_STRING, marg_string_new("z"), \
            OP_TENSOR, marg_string_new("1"), \
            OP_KEYWORD, marg_string_new("attr_reader:"), marg_string_new("1"), \
            OP_VARIABLE, marg_string_new("Point3D"), \
            OP_VARIABLE, marg_string_new("Method"), \
            OP_UNARY, marg_string_new("keyword"), \
            OP_ANY_OBJECT, \
            OP_STRING, marg_string_new("x:y:z:"), \
            OP_METHOD_PARAMETER, marg_string_new("x"), \
            OP_METHOD_PARAMETER, marg_string_new("y"), \
            OP_METHOD_PARAMETER, marg_string_new("z"), \
            OP_TENSOR, marg_string_new("3"), \
            OP_START_PROC, \
                OP_SELF, \
                OP_VARIABLE, marg_string_new("x"), \
                OP_VARIABLE, marg_string_new("y"), \
                OP_VARIABLE, marg_string_new("z"), \
                OP_TENSOR, marg_string_new("4"), \
                OP_SUPER, \
                OP_INSTANCE, marg_string_new("x"), \
                OP_INSTANCE, marg_string_new("y"), \
                OP_KEYWORD, marg_string_new("x:y:"), marg_string_new("2"), \
                OP_VARIABLE, marg_string_new("z"), \
                OP_STORE_INSTANCE, marg_string_new("z"), \
                OP_SELF, \
            OP_END_PROC, \
            OP_KEYWORD, marg_string_new("object:message:params:method:"), marg_string_new("4"), \
            OP_KEYWORD, marg_string_new("message:"), marg_string_new("1"), \
            OP_VARIABLE, marg_string_new("Point3D"), \
            OP_VARIABLE, marg_string_new("Method"), \
            OP_UNARY, marg_string_new("unary"), \
            OP_ANY_OBJECT, \
            OP_STRING, marg_string_new("calc"), \
            OP_START_PROC,
                OP_SELF, \
                OP_TENSOR, marg_string_new("1"), \
                OP_SUPER, \
                OP_UNARY, marg_string_new("calc"), \
                OP_INSTANCE, marg_string_new("z"), \
                OP_BINARY, marg_string_new("+"), \
            OP_END_PROC, \
            OP_KEYWORD, marg_string_new("object:message:method:"), marg_string_new("3"), \
            OP_KEYWORD, marg_string_new("message:"), marg_string_new("1"), \
            OP_VARIABLE, marg_string_new("Point3D"), \
            OP_VARIABLE, marg_string_new("Method"), \
            OP_UNARY, marg_string_new("binary"), \
            OP_ANY_OBJECT, \
            OP_STRING, marg_string_new("+"), \
            OP_METHOD_PARAMETER, marg_string_new("other"), \
            OP_START_PROC, \
                OP_SELF, \
                OP_VARIABLE, marg_string_new("other"), \
                OP_TENSOR, marg_string_new("2"), \
                OP_SUPER, \
                OP_VARIABLE, marg_string_new("other"), \
                OP_BINARY, marg_string_new("+"), \
                OP_INSTANCE, marg_string_new("z"), \
                OP_VARIABLE, marg_string_new("other"), \
                OP_UNARY, marg_string_new("z"), \
                OP_BINARY, marg_string_new("+"), \
                OP_STORE_INSTANCE, marg_string_new("z"), \
                OP_SELF, \
            OP_END_PROC, \
            OP_KEYWORD, marg_string_new("object:message:param:method:"), marg_string_new("4"), \
            OP_KEYWORD, marg_string_new("message:"), marg_string_new("1"), \
            OP_VARIABLE, marg_string_new("Point3D"), \
            OP_INTEGER, marg_string_new("10"), \
            OP_INTEGER, marg_string_new("20"), \
            OP_INTEGER, marg_string_new("30"), \
            OP_KEYWORD, marg_string_new("x:y:z:"), marg_string_new("3"), \
            OP_STORE, marg_string_new("p1"), \
            OP_VARIABLE, marg_string_new("Point3D"), \
            OP_2, \
            OP_INTEGER, marg_string_new("4"), \
            OP_INTEGER, marg_string_new("6"), \
            OP_KEYWORD, marg_string_new("x:y:z:"), marg_string_new("3"), \
            OP_STORE, marg_string_new("p2"), \
            OP_VARIABLE, marg_string_new("p1"), \
            OP_UNARY, marg_string_new("calc"), \
            OP_UNARY, marg_string_new("puts"), \
            OP_VARIABLE, marg_string_new("p2"), \
            OP_UNARY, marg_string_new("calc"), \
            OP_UNARY, marg_string_new("puts"), \
            OP_VARIABLE, marg_string_new("p1"), \
            OP_VARIABLE, marg_string_new("p2"), \
            OP_UNARY, marg_string_new("calc"), \
            OP_BINARY, marg_string_new("+"), \
            OP_UNARY, marg_string_new("puts") \
        ));
    });
})

#endif
