-module(main).

-export([main/0]).

main() ->
  P1 = point3d:new(10, 20, 30),
  P2 = point3d:new(2, 4, 6),

  Result1 = point3d:calc(P1),
  Result2 = point3d:calc(P2),

  io:format("~p~n", [Result1]),
  io:format("~p~n", [Result2]),

  P3 = point3d:add(P1, P2),
  Result3 = point3d:calc(P3),
  io:format("~p~n", [Result3]).
