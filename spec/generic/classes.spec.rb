describe Parser do
    context "on classes" do
        it "parses generating an object with inheritance" do
            parse(%Q{(
                Point = Object subclass,
                Point attr_reader: ["x", "y"],

                Point message: #x: xparam y: yparam => (
                    @x = xparam,
                    @y = yparam,
                    self
                ),

                Point message: #calc => @x + @y,

                Point message: #+ other => (
                    @x = @x + other x,
                    @y = @y + other y,
                    self
                ),

                Point3D = Point subclass,
                Point attr_reader: ["z"],

                Point3D message: #x: x y: y z: z => (
                    super x: @x y: @y,
                    @z = z,
                    self
                ),

                Point3D message: #calc => super calc + @z,

                Point3D message: #+ other => (
                    super + other,
                    @z = @z + other z,
                    self
                ),

                p1 = Point3D x: 10 y: 20 z: 30,
                p2 = Point3D x: 2 y: 4 z: 6,

                p1 calc puts,
                p2 calc puts,
                (p1 + p2 calc) puts
            )}, ["push_variable", "Object", "unary", "subclass", "store", "Point", "push_variable", "Point", "push_string", %Q{"x"}, "push_string", %Q{"y"}, "push_tensor", "2", "keyword", "attr_reader:", "1", "push_variable", "Point", "STARTpush_keyword_method", %Q{"x:y:"}, "push_variable", "xparam", "push_variable", "yparam", "push_tensor", "2", "push_variable", "xparam", "store_instance", "x", "push_variable", "yparam", "store_instance", "y", "push_self", "ENDpush_keyword_method", "keyword", "message:", "1", "push_variable", "Point", "STARTpush_unary_method", %Q{"calc"}, "push_instance", "x", "push_instance", "y", "binary", "+", "ENDpush_unary_method", "keyword", "message:", "1", "push_variable", "Point", "STARTpush_binary_method", %Q{"+"}, "push_variable", "other", "push_instance", "x", "push_variable", "other", "unary", "x", "binary", "+", "store_instance", "x", "push_instance", "y", "push_variable", "other", "unary", "y", "binary", "+", "store_instance", "y", "push_self", "ENDpush_binary_method", "keyword", "message:", "1", "push_variable", "Point", "unary", "subclass", "store", "Point3D", "push_variable", "Point", "push_string", %Q{"z"}, "push_tensor", "1", "keyword", "attr_reader:", "1", "push_variable", "Point3D", "STARTpush_keyword_method", %Q{"x:y:z:"}, "push_variable", "x", "push_variable", "y", "push_variable", "z", "push_tensor", "3", "push_super", "push_instance", "x", "push_instance", "y", "keyword", "x:y:", "2", "push_variable", "z", "store_instance", "z", "push_self", "ENDpush_keyword_method", "keyword", "message:", "1", "push_variable", "Point3D", "STARTpush_unary_method", %Q{"calc"}, "push_super", "unary", "calc", "push_instance", "z", "binary", "+", "ENDpush_unary_method", "keyword", "message:", "1", "push_variable", "Point3D", "STARTpush_binary_method", %Q{"+"}, "push_variable", "other", "push_super", "push_variable", "other", "binary", "+", "push_instance", "z", "push_variable", "other", "unary", "z", "binary", "+", "store_instance", "z", "push_self", "ENDpush_binary_method", "keyword", "message:", "1", "push_variable", "Point3D", "push_integer", "10", "push_integer", "20", "push_integer", "30", "keyword", "x:y:z:", "3", "store", "p1", "push_variable", "Point3D", "push_2", "push_integer", "4", "push_integer", "6", "keyword", "x:y:z:", "3", "store", "p2", "push_variable", "p1", "unary", "calc", "unary", "puts", "push_variable", "p2", "unary", "calc", "unary", "puts", "push_variable", "p1", "push_variable", "p2", "unary", "calc", "binary", "+", "unary", "puts"]);
        end
    end
end
