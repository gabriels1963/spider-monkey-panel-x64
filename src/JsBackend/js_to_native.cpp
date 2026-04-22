#include "PCH.hpp"
#include "js_to_native.h"

namespace mozjs::convert::to_native
{
	namespace internal
	{
		void check_js_value(const JS::HandleValue& jsValue)
		{
			QwrException::ExpectTrue(jsValue.isNumber(), "jsValue not a number");
		}

		void check_num(auto num)
		{
			QwrException::ExpectTrue(!std::isnan(num) && !std::isinf(num), "Infinity/NaN error");
		}

		template <>
		bool ToSimpleValue(JSContext*, const JS::HandleValue& jsValue)
		{
			return JS::ToBoolean(jsValue);
		}

		template <>
		int32_t ToSimpleValue(JSContext* ctx, const JS::HandleValue& jsValue)
		{
			check_js_value(jsValue);
			int32_t val{};
			QwrException::ExpectTrue(JS::ToInt32(ctx, jsValue, &val), "jsValue not a number");
			check_num(val);
			return val;
		}

		template <>
		uint8_t ToSimpleValue(JSContext* ctx, const JS::HandleValue& jsValue)
		{
			check_js_value(jsValue);
			uint8_t val{};
			QwrException::ExpectTrue(JS::ToUint8(ctx, jsValue, &val), "jsValue not a number");
			check_num(val);
			return val;
		}

		template <>
		uint32_t ToSimpleValue(JSContext* ctx, const JS::HandleValue& jsValue)
		{
			check_js_value(jsValue);
			uint32_t val{};
			QwrException::ExpectTrue(JS::ToUint32(ctx, jsValue, &val), "jsValue not a number");
			check_num(val);
			return val;
		}

		template <>
		uint64_t ToSimpleValue(JSContext* ctx, const JS::HandleValue& jsValue)
		{
			check_js_value(jsValue);
			uint64_t val{};
			QwrException::ExpectTrue(JS::ToUint64(ctx, jsValue, &val), "jsValue not a number");
			check_num(val);
			return val;
		}

		template <>
		float ToSimpleValue(JSContext* ctx, const JS::HandleValue& jsValue)
		{
			check_js_value(jsValue);
			double val{};
			QwrException::ExpectTrue(JS::ToNumber(ctx, jsValue, &val), "jsValue not a number");
			check_num(val);
			return static_cast<float>(val);
		}

		template <>
		double ToSimpleValue(JSContext* ctx, const JS::HandleValue& jsValue)
		{
			check_js_value(jsValue);
			double val{};
			QwrException::ExpectTrue(JS::ToNumber(ctx, jsValue, &val), "jsValue not a number");
			check_num(val);
			return val;
		}

		template <>
		std::string ToSimpleValue(JSContext* ctx, const JS::HandleValue& jsValue)
		{
			auto jsString = JS::RootedString(ctx, JS::ToString(ctx, jsValue));
			return ToValue<std::string>(ctx, jsString);
		}

		template <>
		std::wstring ToSimpleValue(JSContext* ctx, const JS::HandleValue& jsValue)
		{
			auto jsString = JS::RootedString(ctx, JS::ToString(ctx, jsValue));
			return ToValue<std::wstring>(ctx, jsString);
		}

		template <>
		std::nullptr_t ToSimpleValue(JSContext*, const JS::HandleValue&)
		{
			return nullptr;
		}
	}

	template <>
	std::string ToValue(JSContext* ctx, const JS::HandleString& jsString)
	{
		return smp::ToU8(ToValue<std::wstring>(ctx, jsString));
	}

	template <>
	std::wstring ToValue(JSContext* ctx, const JS::HandleString& jsString)
	{
		const auto size = JS_GetStringLength(jsString);
		if (size == 0uz)
			return {};

		std::wstring wStr;
		wStr.resize(size);
		mozilla::Range<char16_t> wCharStr(reinterpret_cast<char16_t*>(wStr.data()), size);

		QwrException::ExpectTrue(JS_CopyStringChars(ctx, wCharStr, jsString), "Internal JS_CopyStringChars error");
		return wStr;
	}
}
