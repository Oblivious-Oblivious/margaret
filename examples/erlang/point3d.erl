-module(point3d).

-export([new/3, calc/1, add/2]).

-include("point3d.hrl").

new(X, Y, Z) ->
  #point3d{x = X,
           y = Y,
           z = Z}.

calc(#point3d{x = X,
              y = Y,
              z = Z}) ->
  SuperResult = point:calc(#point{x = X, y = Y}),
  SuperResult + Z.

add(#point3d{x = X1,
             y = Y1,
             z = Z1},
    #point3d{x = X2,
             y = Y2,
             z = Z2}) ->
  PointResult = point:add(#point{x = X1, y = Y1}, #point{x = X2, y = Y2}),
  #point{x = NewX, y = NewY} = PointResult,
  new(NewX, NewY, Z1 + Z2).
