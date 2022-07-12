require_relative "_parser_helpers";

describe Parser do
    context "on classes" do
        it "parses generating an object with inheritance" do
            # TODO Fix self and super interactions
            parse(%Q{
                (
                    (Object subclass: "Point")
                    (Point
                        message: "x"
                        params: ("x" "y")
                        method: (
                            (self x = x)
                            (self y = y)
                        )
                    )
                    (Point
                        message: "calc"
                        params: ()
                        method: (
                            (self x) + (self y)
                        )
                    )
                    (Point subclass: :Point3D)
                    (Point3D
                        message: :new
                        params: (:x :y :z)
                        method: (
                            (super x: (self x) y: (self y))
                            (self z = z)
                        )
                    )
                    (Point3D
                        message: :calc
                        params: ()
                        method: (
                            (super calc) + (self z)
                        )
                    )
                    (p = Point3D new: 10 y: 20 z: 30)
                    (p calc)
                )
            });
        end

        it "creates a class using specialized syntax" do
            parse(%Q{(
                (Object
                    subclass: "Point"
                    message: ("new" ("x" "y") (
                        (self x = x)
                        (self y = y)
                    ));
                    message: ("calc" () (
                        (self x) + (self y)
                    ))
                )
                (Point
                    subclass: "Point3D"
                    message: ("new" ("x" "y" "z") (
                        (super new: (self x) y: (self y))
                        (self z = z)
                    ));
                    message: ("calc" () (
                        (super calc) + (self z)
                    ))
                )
                (p = Point3D new: 10 y: 20 z: 30)
                (p calc)
            )});
        end
    end
end
