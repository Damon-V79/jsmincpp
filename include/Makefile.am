nobase_include_HEADERS = \
	jsmincpp/ConstString.h \
	jsmincpp/deserialize/CRC32Hash.h \
	jsmincpp/deserialize/Deserializer.h \
	jsmincpp/deserialize/GetNameHash.h \
	jsmincpp/deserialize/GetNameHash.rlh \
	jsmincpp/deserialize/MallocCreator.h \
	jsmincpp/deserialize/Params.h \
	jsmincpp/deserialize/ParseBool.h \
	jsmincpp/deserialize/ParseBool.rlh \
	jsmincpp/deserialize/ParseFloat.h \
	jsmincpp/deserialize/ParseFloat.rlh \
	jsmincpp/deserialize/ParseInt.h \
	jsmincpp/deserialize/ParseInt.rlh \
	jsmincpp/deserialize/ParseStaticString.h \
	jsmincpp/deserialize/ParseStaticString.rlh \
	jsmincpp/deserialize/ParseUInt.h \
	jsmincpp/deserialize/ParseUInt.rlh \
	jsmincpp/deserialize/SkipEndJSONString.h \
	jsmincpp/deserialize/SkipEndJSONString.rlh \
	jsmincpp/deserialize/STLSupport/Deque.h \
	jsmincpp/deserialize/STLSupport/ForwardList.h \
	jsmincpp/deserialize/STLSupport/List.h \
	jsmincpp/deserialize/STLSupport/Map.h \
	jsmincpp/deserialize/STLSupport/ParseStdString.h \
	jsmincpp/deserialize/STLSupport/ParseStdString.rlh \
	jsmincpp/deserialize/STLSupport/Set.h \
	jsmincpp/deserialize/STLSupport/SharedPrtCreator.h \
	jsmincpp/deserialize/STLSupport/STLContiners.h \
	jsmincpp/deserialize/STLSupport/String.h \
	jsmincpp/deserialize/STLSupport/Vector.h \
	jsmincpp/deserialize/Tuple.h \
	jsmincpp/FloatPoint_3x1.h \
	jsmincpp/IntegerOverflowControl.h \
	jsmincpp/serialize/JSONSerializer.h \
	jsmincpp/serialize/Serializer.h \
	jsmincpp/serialize/STLSupport/Deque.h \
	jsmincpp/serialize/STLSupport/ForwardList.h \
	jsmincpp/serialize/STLSupport/List.h \
	jsmincpp/serialize/STLSupport/Map.h \
	jsmincpp/serialize/STLSupport/Set.h \
	jsmincpp/serialize/STLSupport/String.h \
	jsmincpp/serialize/STLSupport/Vector.h \
	jsmincpp/StaticString.h \
	jsmincpp/TypesUtilities.h



RM := rm
ECHO := echo

RL := ragel
RLFLAGS := -G2

source_dirs     := $(top_srcdir)/include/jsmincpp/deserialize $(top_srcdir)/include/jsmincpp/deserialize/STLSupport
generated_files := $(patsubst %.rlh,  %.h, $(wildcard $(addsuffix /*.rlh,  $(source_dirs))))

BUILT_SOURCES := $(generated_files)

%.rlh:

%.h: %.rlh
	@$(ECHO) Compile $<
	$(RL) $(RLFLAGS) $< -p -o $(patsubst %.rlh, %.h, $<)

clean:
	$(RM) -f $(generated_files)
