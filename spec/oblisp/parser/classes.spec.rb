require_relative "_parser_helpers";

describe Parser do
    context "on classes" do
        it "parses generating an object with inheritance" do
            pp parse(%Q{
                (
                    (Object subclass: "Point")
                    (Point
                        message: "x:y:"
                        params: ("xparam" "yparam")
                        method: (
                            ((Point x) = xparam)
                            ((Point y) = yparam)
                        )
                    )
                    (Point
                        message: "calc"
                        params: ()
                        method: (
                            (Point x) + (Point y)
                        )
                    )
                    (Point subclass: :Point3D)
                    (Point3D
                        message: "new:y:z:"
                        params: (:x :y :z)
                        method: (
                            (Point x: (Point3D x) y: (Point3D y))
                            ((Point3D z) = z)
                        )
                    )
                    (Point3D
                        message: "calc"
                        params: ()
                        method: (
                            (Point calc) + (Point3D z)
                        )
                    )
                    (p = Point3D new: 10 y: 20 z: 30)
                    (p calc)
                )
            }, %Q{((subclass: Object "Point") (message:params:method: Point "x:y:" ("xparam" "yparam") ((= ((x Point)) xparam) (= ((y Point)) yparam))) (message:params:method: Point "calc" () (+ ((x Point)) (y Point))) (subclass: Point (new Symbol "Point3D")) (message:params:method: Point3D "new:y:z:" (new Symbol "x" new Symbol "y" new Symbol "z") ((x:y: Point (x Point3D) (y Point3D)) (= ((z Point3D)) z))) (message:params:method: Point3D "calc" () (+ ((calc Point)) (z Point3D))) (= p (new:y:z: Point3D 10 20 30)) (calc p))});
        end

        it "creates a class using specialized syntax" do
            parse(%Q{(
                (Object subclass: "Point")
                (Point
                    message: ("new:y:" ("x" "y") (
                        ((Point x) = x)
                        ((Point y) = y)
                    ));
                    message: ("calc" () (
                        (Point x) + (Point y)
                    ))
                )
                (Point subclass: "Point3D")
                (Point3D
                    message: ("new:y:z:" ("x" "y" "z") (
                        (Point new: (Point3D x) y: (Point3D y))
                        ((Point3D z) = z)
                    ));
                    message: ("calc" () (
                        (Point calc) + (Point3D z)
                    ))
                )
                (p = Point3D new: 10 y: 20 z: 30)
                (p calc)
            )}, %Q{((subclass: Object "Point") ((message: Point ("new:y:" ("x" "y") ((= ((x Point)) x) (= ((y Point)) y)))) (message: Point ("calc" () (+ ((x Point)) (y Point))))) (subclass: Point "Point3D") ((message: Point3D ("new:y:z:" ("x" "y" "z") ((new:y: Point (x Point3D) (y Point3D)) (= ((z Point3D)) z)))) (message: Point3D ("calc" () (+ ((calc Point)) (z Point3D))))) (= p (new:y:z: Point3D 10 20 30)) (calc p))});
        end
    end
end
