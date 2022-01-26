TARGET_FILES=.

format:
	autoflake -i --ignore-init-module-imports --remove-all-unused-imports -r $(TARGET_FILES)
	black --line-length 100 $(TARGET_FILES)
	isort $(TARGET_FILES) --line-length 100

style_check:
	autoflake --ignore-init-module-imports --remove-all-unused-imports -r $(TARGET_FILES)
	black --diff --check --line-length 100 $(TARGET_FILES)
	isort -c $(TARGET_FILES) --line-length 100

unittest:
	PYTHONPATH="${PYTHONPATH}:." pytest --cov=facerec --no-cov-on-fail --cov-report=html:html_cov/ --cov-report term tests
