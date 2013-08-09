#include "Translator.h"

#include <locale.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Properties Translator::props;

void Translator::init(const char *locale) {
	char path[50];
	memset(path, '\0', 50);
	sprintf(path, "resources/languages/%s.properties", locale);
	props.load(path);
}

const char *Translator::translate(const char *key) {
	const char *value = props.getProperty(key);
	return value ? value : key;
}

