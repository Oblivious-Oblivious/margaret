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
                @self \
            ), \
            \
            Point bind: #calc => @x + @y, \
            \
            Point multibind: [ \
                # + $nil => @self, \
                # + other => ( \
                    @x = @x + other x, \
                    @y = @y + other y, \
                    @self \
                ) \
            ], \
            Point3D = Point subclass, \
            Point attr_reader: [\"z\"], \
            \
            Point3D bind: #x: x y: y z: z => ( \
                @super x: @x y: @y, \
                @z = z, \
                @self \
            ), \
            \
            Point3D bind: #calc => @super calc + @z, \
            \
            Point3D bind: #+ other => ( \
                @super + other, \
                @z = @z + other z, \
                @self \
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
            FM_POP, \
            FM_LOCAL, string_new("Point"), \
            FM_STRING, string_new("x"), \
            FM_POP, \
            FM_STRING, string_new("y"), \
            FM_POP, \
            FM_TENSOR, string_new("2"), \
            FM_KEYWORD, string_new("attr_reader:"), string_new("1"), \
            FM_POP, \
            FM_LOCAL, string_new("Point"), \
            FM_START_KEYWORD_METHOD, string_new("x:y:"), \
                FM_ANY_OBJECT, FM_METHOD_RECEIVER, \
                FM_LOCAL, string_new("xparam"), FM_METHOD_PARAMETER, \
                FM_LOCAL, string_new("yparam"), FM_METHOD_PARAMETER, \
                FM_LOCAL, string_new("xparam"), \
                FM_STORE_INSTANCE, string_new("x"), \
                FM_POP, \
                FM_LOCAL, string_new("yparam"), \
                FM_STORE_INSTANCE, string_new("y"), \
                FM_POP, \
                FM_SELF, \
                FM_POP, \
            FM_END_KEYWORD_METHOD, \
            FM_KEYWORD, string_new("bind:"), string_new("1"), \
            FM_POP, \
            FM_LOCAL, string_new("Point"), \
            FM_START_UNARY_METHOD, string_new("calc"), \
                FM_ANY_OBJECT, FM_METHOD_RECEIVER, \
                FM_INSTANCE, string_new("x"), \
                FM_INSTANCE, string_new("y"), \
                FM_BINARY, string_new("+"), \
                FM_POP, \
            FM_END_UNARY_METHOD, \
            FM_KEYWORD, string_new("bind:"), string_new("1"), \
            FM_POP, \
            FM_LOCAL, string_new("Point"), \
            FM_START_BINARY_METHOD, string_new("+"), \
                FM_ANY_OBJECT, FM_METHOD_RECEIVER, \
                FM_NIL, FM_METHOD_PARAMETER, \
                FM_SELF, \
                FM_POP, \
            FM_END_BINARY_METHOD, \
            FM_POP, \
            FM_START_BINARY_METHOD, string_new("+"), \
                FM_ANY_OBJECT, FM_METHOD_RECEIVER, \
                FM_LOCAL, string_new("other"), FM_METHOD_PARAMETER, \
                FM_INSTANCE, string_new("x"), \
                FM_LOCAL, string_new("other"), \
                FM_UNARY, string_new("x"), \
                FM_BINARY, string_new("+"), \
                FM_STORE_INSTANCE, string_new("x"), \
                FM_POP, \
                FM_INSTANCE, string_new("y"), \
                FM_LOCAL, string_new("other"), \
                FM_UNARY, string_new("y"), \
                FM_BINARY, string_new("+"), \
                FM_STORE_INSTANCE, string_new("y"), \
                FM_POP, \
                FM_SELF, \
                FM_POP, \
            FM_END_BINARY_METHOD, \
            FM_POP, \
            FM_TENSOR, string_new("2"),
            FM_KEYWORD, string_new("multibind:"), string_new("1"), \
            FM_POP, \
            FM_LOCAL, string_new("Point"), \
            FM_UNARY, string_new("subclass"), \
            FM_STORE_LOCAL, string_new("Point3D"), \
            FM_POP, \
            FM_LOCAL, string_new("Point"), \
            FM_STRING, string_new("z"), \
            FM_POP, \
            FM_TENSOR, string_new("1"), \
            FM_KEYWORD, string_new("attr_reader:"), string_new("1"), \
            FM_POP, \
            FM_LOCAL, string_new("Point3D"), \
            FM_START_KEYWORD_METHOD, string_new("x:y:z:"), \
                FM_ANY_OBJECT, FM_METHOD_RECEIVER, \
                FM_LOCAL, string_new("x"), FM_METHOD_PARAMETER, \
                FM_LOCAL, string_new("y"), FM_METHOD_PARAMETER, \
                FM_LOCAL, string_new("z"), FM_METHOD_PARAMETER, \
                FM_SUPER, \
                FM_INSTANCE, string_new("x"), \
                FM_INSTANCE, string_new("y"), \
                FM_KEYWORD, string_new("x:y:"), string_new("2"), \
                FM_POP, \
                FM_LOCAL, string_new("z"), \
                FM_STORE_INSTANCE, string_new("z"), \
                FM_POP, \
                FM_SELF, \
                FM_POP, \
            FM_END_KEYWORD_METHOD, \
            FM_KEYWORD, string_new("bind:"), string_new("1"), \
            FM_POP, \
            FM_LOCAL, string_new("Point3D"), \
            FM_START_UNARY_METHOD, string_new("calc"), \
                FM_ANY_OBJECT, FM_METHOD_RECEIVER, \
                FM_SUPER, \
                FM_UNARY, string_new("calc"), \
                FM_INSTANCE, string_new("z"), \
                FM_BINARY, string_new("+"), \
                FM_POP, \
            FM_END_UNARY_METHOD, \
            FM_KEYWORD, string_new("bind:"), string_new("1"), \
            FM_POP, \
            FM_LOCAL, string_new("Point3D"), \
            FM_START_BINARY_METHOD, string_new("+"), \
                FM_ANY_OBJECT, FM_METHOD_RECEIVER, \
                FM_LOCAL, string_new("other"), FM_METHOD_PARAMETER, \
                FM_SUPER, \
                FM_LOCAL, string_new("other"), \
                FM_BINARY, string_new("+"), \
                FM_POP, \
                FM_INSTANCE, string_new("z"), \
                FM_LOCAL, string_new("other"), \
                FM_UNARY, string_new("z"), \
                FM_BINARY, string_new("+"), \
                FM_STORE_INSTANCE, string_new("z"), \
                FM_POP, \
                FM_SELF, \
                FM_POP, \
            FM_END_BINARY_METHOD, \
            FM_KEYWORD, string_new("bind:"), string_new("1"), \
            FM_POP, \
            FM_LOCAL, string_new("Point3D"), \
            FM_INTEGER, string_new("10"), \
            FM_INTEGER, string_new("20"), \
            FM_INTEGER, string_new("30"), \
            FM_KEYWORD, string_new("x:y:z:"), string_new("3"), \
            FM_STORE_LOCAL, string_new("p1"), \
            FM_POP, \
            FM_LOCAL, string_new("Point3D"), \
            FM_INTEGER, string_new("2"), \
            FM_INTEGER, string_new("4"), \
            FM_INTEGER, string_new("6"), \
            FM_KEYWORD, string_new("x:y:z:"), string_new("3"), \
            FM_STORE_LOCAL, string_new("p2"), \
            FM_POP, \
            FM_LOCAL, string_new("p1"), \
            FM_UNARY, string_new("calc"), \
            FM_UNARY, string_new("puts"), \
            FM_POP, \
            FM_LOCAL, string_new("p2"), \
            FM_UNARY, string_new("calc"), \
            FM_UNARY, string_new("puts"), \
            FM_POP, \
            FM_LOCAL, string_new("p1"), \
            FM_LOCAL, string_new("p2"), \
            FM_UNARY, string_new("calc"), \
            FM_BINARY, string_new("+"), \
            FM_UNARY, string_new("puts"), \
            FM_POP \
        ));
    });

    it("parses multibinds", {
        parse("( \
            Point = $Margaret clone: [ \
                # x: x y: y => ( \
                    @x = x, \
                    @y = y, \
                    @self clone, \
                ), \
                # + $nil => @self, \
                # + other => ( \
                    @x = @x + other x, \
                    @y = @y + other y, \
                    @self, \
                ), \
            ], \
            Point attr_reader: [\"@x\", \"@y\"], \
            \
            p1 = Point x: 2 y: 3, \
            p2 = Point x: 5 y: 7, \
            p3 = p1 + p2, \
            puts: p3, \
        )", vector_new( \
            FM_GLOBAL, string_new("Margaret"), \
            FM_START_KEYWORD_METHOD, string_new("x:y:"), \
                FM_ANY_OBJECT, FM_METHOD_RECEIVER, \
                FM_LOCAL, string_new("x"), FM_METHOD_PARAMETER, \
                FM_LOCAL, string_new("y"), FM_METHOD_PARAMETER, \
                FM_LOCAL, string_new("x"), \
                FM_STORE_INSTANCE, string_new("x"), \
                FM_POP, \
                FM_LOCAL, string_new("y"), \
                FM_STORE_INSTANCE, string_new("y"), \
                FM_POP, \
                FM_SELF, \
                FM_UNARY, string_new("clone"), \
                FM_POP, \
            FM_END_KEYWORD_METHOD, \
            FM_POP, \
            FM_START_BINARY_METHOD, string_new("+"), \
                FM_ANY_OBJECT, FM_METHOD_RECEIVER, \
                FM_NIL, FM_METHOD_PARAMETER, \
                FM_SELF, \
                FM_POP, \
            FM_END_BINARY_METHOD, \
            FM_POP, \
            FM_START_BINARY_METHOD, string_new("+"), \
                FM_ANY_OBJECT, FM_METHOD_RECEIVER, \
                FM_LOCAL, string_new("other"), FM_METHOD_PARAMETER, \
                FM_INSTANCE, string_new("x"), \
                FM_LOCAL, string_new("other"), \
                FM_UNARY, string_new("x"), \
                FM_BINARY, string_new("+"), \
                FM_STORE_INSTANCE, string_new("x"), \
                FM_POP, \
                FM_INSTANCE, string_new("y"), \
                FM_LOCAL, string_new("other"), \
                FM_UNARY, string_new("y"), \
                FM_BINARY, string_new("+"), \
                FM_STORE_INSTANCE, string_new("y"), \
                FM_POP, \
                FM_SELF, \
                FM_POP, \
            FM_END_BINARY_METHOD, \
            FM_POP, \
            FM_TENSOR, string_new("3"), \
            FM_KEYWORD, string_new("clone:"), string_new("1"), \
            FM_STORE_LOCAL, string_new("Point"), \
            FM_POP, \
            FM_LOCAL, string_new("Point"), \
            FM_STRING, string_new("@x"), \
            FM_POP, \
            FM_STRING, string_new("@y"), \
            FM_POP, \
            FM_TENSOR, string_new("2"), \
            FM_KEYWORD, string_new("attr_reader:"), string_new("1"), \
            FM_POP, \
            FM_LOCAL, string_new("Point"), \
            FM_INTEGER, string_new("2"), \
            FM_INTEGER, string_new("3"), \
            FM_KEYWORD, string_new("x:y:"), string_new("2"), \
            FM_STORE_LOCAL, string_new("p1"),
            FM_POP, \
            FM_LOCAL, string_new("Point"), \
            FM_INTEGER, string_new("5"), \
            FM_INTEGER, string_new("7"), \
            FM_KEYWORD, string_new("x:y:"), string_new("2"), \
            FM_STORE_LOCAL, string_new("p2"), \
            FM_POP, \
            FM_LOCAL, string_new("p1"), \
            FM_LOCAL, string_new("p2"), \
            FM_BINARY, string_new("+"), \
            FM_STORE_LOCAL, string_new("p3"), \
            FM_POP, \
            FM_GLOBAL, string_new("Margaret"), \
            FM_LOCAL, string_new("p3"), \
            FM_KEYWORD, string_new("puts:"), string_new("1"), \
            FM_POP \
        ));
    });
})

#endif
