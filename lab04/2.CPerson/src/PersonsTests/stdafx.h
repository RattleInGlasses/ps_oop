// stdafx.h: включаемый файл дл€ стандартных системных включаемых файлов
// или включаемых файлов дл€ конкретного проекта, которые часто используютс€, но
// не часто измен€ютс€
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <string>
#include <vector>
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <memory>
#include <list>
#pragma warning(push)
#pragma warning(disable: 4127)
#include <boost/range/algorithm/equal.hpp>
#pragma warning(pop)
#include <boost/optional.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/tokenizer.hpp>


// TODO: ”становите здесь ссылки на дополнительные заголовки, требующиес€ дл€ программы

#define BOOST_TEST_INCLUDED
#pragma warning (disable: 4702)
#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string/replace.hpp>
