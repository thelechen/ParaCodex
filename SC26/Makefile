SHELL := /bin/sh

SC26_DIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
DEMO_DIR := $(SC26_DIR)/tutorial_demo/paracodex_opencode
RUN_DIR := $(DEMO_DIR)/runs/latest
WORK_DIR := $(DEMO_DIR)/work

.PHONY: clean help

help:
	@printf '%s\n' \
		'SC26 ParaCodex hands-on' \
		'' \
		'  make clean  Remove generated run and agent-work artifacts so the exercise can be rerun'

clean:
	@test -f "$(SC26_DIR)/SC26_PARACODEX_START_HERE.md"
	@test -f "$(DEMO_DIR)/tools/gate.py"
	@rm -rf -- \
		"$(RUN_DIR)" \
		"$(DEMO_DIR)/tools/__pycache__" \
		"$(DEMO_DIR)/__pycache__" \
		"$(DEMO_DIR)/.pytest_cache"
	@find "$(WORK_DIR)" -mindepth 1 -maxdepth 1 ! -name '.gitkeep' -exec rm -rf -- {} +
	@printf '%s\n' \
		'Cleaned generated ParaCodex run and agent-work artifacts.' \
		'Source code, the golden reference, tests, QA evidence, .opencode configuration, and this Makefile were preserved.'
