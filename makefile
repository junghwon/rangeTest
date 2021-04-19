SRC = 	main.c \
		rangeController.c	\
		rangeKeyController.c	\
		rangeCookModel.c	\
		rangeMagnetronModel.c	\
		rangeRelayModel.c	\
		rangeTimer_Model.c	\
		rangeView.c	\

OBJ = $(SRC:%.c=%.o)

.PHONY: rangeTest
rangeTest:
	gcc $(SRC) -o $@  -lpthread 

.PHONY: clean
clean: $(OBJ)
	rm $(OBJ) rangeTest