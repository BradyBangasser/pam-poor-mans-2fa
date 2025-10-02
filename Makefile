OUT:=out
SRC:=.
SO:=pmf.so
IP:=/lib64/security

all: out $(SO)

clean:
	rm -rf out $(SO)

install: all
	sudo cp $(SO) $(IP)/pam_$(SO)
	sudo chmod 644 $(IP)/pam_$(SO)
	sudo chown root:root $(IP)/pam_$(SO)

uninstall:
	sudo rm -rf $(IP)/pam_$(SO)

out:
	mkdir -p $(OUT)

$(SO): $(OUT)/pmf.c.o
	$(CC) -shared -fPIC -o $@ $^

$(OUT)/%.c.o: $(SRC)/%.c
	$(CC) -c -fPIC $^ -o $@

.PHONY: all clean uninstall install
