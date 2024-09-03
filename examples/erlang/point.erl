-module(point).

-export([new/2, calc/1, add/2]).

-include("point.hrl").

new(X, Y) ->
  #point{x = X, y = Y}.

calc(#point{x = X, y = Y}) ->
  X + Y.

add(#point{x = X1, y = Y1}, #point{x = X2, y = Y2}) ->
  new(X1 + X2, Y1 + Y2).
