require_relative "_parser_helpers";

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
            )}, %Q{(= Point subclass Object, attr_reader: Point new Tuple ("x", "y"), message: Point selector:block: Method "x:y:" params:function: Block (xparam, yparam) (= @x xparam, = @y yparam, self), message: Point selector:block: Method "calc" params:function: Block () + @x @y, message: Point selector:block: Method "+" params:function: Block (other) (= @x + @x x other, = @y + @y y other, self), = Point3D subclass Point, attr_reader: Point new Tuple ("z"), message: Point3D selector:block: Method "x:y:z:" params:function: Block (x, y, z) (x:y: super @x @y, = @z z, self), message: Point3D selector:block: Method "calc" params:function: Block () + calc super @z, message: Point3D selector:block: Method "+" params:function: Block (other) (+ super other, = @z + @z z other, self), = p1 x:y:z: Point3D 10 20 30, = p2 x:y:z: Point3D 2 4 6, puts (calc p1), puts (calc p2), puts (+ p1 calc p2))});
        end
    end
end
