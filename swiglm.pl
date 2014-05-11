:- use_foreign_library(foreign(swiglm)).

transform(InputList, OutputList) :- transform(InputList, OutputList, [[1.0,0.0,0.0,0.0],
																	  [0.0,1.0,0.0,0.0],
																	  [0.0,0.0,1.0,0.0],
																	  [0.0,0.0,0.0,1.0]]).

transform([], Acc, Acc).
transform([H|T], OutputList, Acc) :- mul_matrix(Acc, H, Multiplied), transform(T, OutputList, Multiplied).