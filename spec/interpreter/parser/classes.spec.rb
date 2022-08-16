require_relative "_parser_helpers";

describe Parser do
    context "on classes" do
        it "parses generating an object with inheritance" do
            parse(%Q{(
                Object subclass: "Point",
                Point attr_reader: [:x, :y],

                Point message: (x::xparam, y::yparam, `(
                    @x = xparam,
                    @y = yparam,
                    self
                )),
                Comment new: "->(:xparam, :yparam, (@x = xparam, @y = yparam, self))",

                Point message: (:calc, `(@x + @y)),
                Comment new: "->(@x + @y)",

                Point message: (:+, :other, `(
                    @x = @x + other x,
                    @y = @y + other y,
                    self
                )),
                Comment new: "->(:other, (@x = @x + other x, @y = @y + other y, self))",

                Point subclass: :Point3D,
                Point attr_reader: [:z],

                Point3D message: (x::x, y::y, z::z, `(
                    super x: @x y: @y,
                    @z = z,
                    self
                )),

                Point3D message: (:calc, `(super calc + @z)),

                Point3D message: (:+, :other, `(
                    super + other,
                    @z = @z + other z,
                    self
                )),

                p1 = Point3D x: 10 y: 20 z: 30,
                p2 = Point3D x: 2 y: 4 z: 6,

                p1 calc puts,
                p2 calc puts,
                (p1 + p2 calc) puts
            )}, %Q{(subclass: Object "Point", attr_reader: Point new Tuple (:"x", :"y"), message: Point (:"x": :"xparam", :"y": :"yparam", (:"(", :"@", :"x", :"=", :"xparam", :",", :"@", :"y", :"=", :"yparam", :",", :"self", :")")), new: Comment "->(:xparam, :yparam, (@x = xparam, @y = yparam, self))", message: Point (:"calc", (:"(", :"@", :"x", :"+", :"@", :"y", :")")), new: Comment "->(@x + @y)", message: Point (:"+", :"other", (:"(", :"@", :"x", :"=", :"@", :"x", :"+", :"other", :"x", :",", :"@", :"y", :"=", :"@", :"y", :"+", :"other", :"y", :",", :"self", :")")), new: Comment "->(:other, (@x = @x + other x, @y = @y + other y, self))", subclass: Point :"Point3D", attr_reader: Point new Tuple (:"z"), message: Point3D (:"x": :"x", :"y": :"y", :"z": :"z", (:"(", :"super", :"x", :":", :"@", :"x", :"y", :":", :"@", :"y", :",", :"@", :"z", :"=", :"z", :",", :"self", :")")), message: Point3D (:"calc", (:"(", :"super", :"calc", :"+", :"@", :"z", :")")), message: Point3D (:"+", :"other", (:"(", :"super", :"+", :"other", :",", :"@", :"z", :"=", :"@", :"z", :"+", :"other", :"z", :",", :"self", :")")), = p1 x:y:z: Point3D 10 20 30, = p2 x:y:z: Point3D 2 4 6, puts (calc p1), puts (calc p2), puts (+ p1 calc p2))});
        end
    end
end
