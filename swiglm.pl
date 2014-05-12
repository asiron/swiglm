:- use_foreign_library(foreign(swiglm)).

transform(InputList, OutputList) :- transform(InputList, OutputList, [[1.0,0.0,0.0,0.0],
																	  [0.0,1.0,0.0,0.0],
																	  [0.0,0.0,1.0,0.0],
																	  [0.0,0.0,0.0,1.0]]).

transform([], Acc, Acc).
transform([H|T], OutputList, Acc) :- mul_matrix(Acc, H, Multiplied), transform(T, OutputList, Multiplied).


transform2(InputList, OutputList) :- transform2(InputList, OutputList, ['M',[[1.0,0.0,0.0,0.0],
																	   		[0.0,1.0,0.0,0.0],
																	   		[0.0,0.0,1.0,0.0],
																	   		[0.0,0.0,0.0,1.0]]]).
transform2([], Acc, Acc).
transform2([['M',Matrix]|T], OutputList, ['M',Acc]) :- mul_matrix(Acc, Matrix, Multiplied), 
													   transform2(T, OutputList, ['M',Multiplied]).

transform2([['Q',[Vec,Quat]]|T], OutputList, ['M',Acc]) :- convert_to_mat(Vec,Quat,Converted),
														   mul_matrix(Acc, Converted, Multiplied),
														   transform2(T,OutputList,['M',Multiplied]).