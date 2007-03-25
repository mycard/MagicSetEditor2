//+----------------------------------------------------------------------------+
//| Description:  Magic Set Editor - Program to make Magic (tm) cards          |
//| Copyright:    (C) 2001 - 2006 Twan van Laarhoven                           |
//| License:      GNU General Public License 2 or later (see file COPYING)     |
//+----------------------------------------------------------------------------+

#ifndef HEADER_SCRIPT_FUNCTIONS_UTIL
#define HEADER_SCRIPT_FUNCTIONS_UTIL

/** @file script/functions/util.cpp
 *
 *  @brief Utility macros for defining script functions.
 */

// ----------------------------------------------------------------------------- : Includes

#include <util/prec.hpp>
#include <util/error.hpp>
#include <script/to_value.hpp>
#include <script/context.hpp>

// ----------------------------------------------------------------------------- : Functions

/// Macro to declare a new script function
/** Usage:
 *  @code
 *   SCRIPT_FUNCTION(my_function) {
 *      // function code goes here
 *   }
 *  @endcode
 *  This declares a value 'script_my_function' which can be added as a variable to a context
 *  using:
 *  @code
 *   extern ScriptValueP script_my_function;
 *   context.setVariable("my_function", script_my_function);
 *  @endcode
 */
#define SCRIPT_FUNCTION(name) SCRIPT_FUNCTION_AUX(name,;)

/// Macro to declare a new script function with custom dependency handling
#define SCRIPT_FUNCTION_WITH_DEP(name)									\
		SCRIPT_FUNCTION_AUX(name, virtual ScriptValueP dependencies(Context&, const Dependency&) const;)

#define SCRIPT_FUNCTION_DEPENDENCIES(name)								\
		ScriptValueP ScriptBuildin_##name::dependencies(Context& ctx, const Dependency& dep) const

// helper for SCRIPT_FUNCTION and SCRIPT_FUNCTION_DEP
#define SCRIPT_FUNCTION_AUX(name,dep)									\
		class ScriptBuildin_##name : public ScriptValue {				\
			dep															\
			virtual  ScriptType type() const							\
				{ return SCRIPT_FUNCTION; }								\
			virtual String typeName() const								\
				{ return _("build in function '") _(#name) _("'"); }	\
			virtual ScriptValueP eval(Context&) const;					\
		};																\
		ScriptValueP script_##name(new ScriptBuildin_##name);			\
		ScriptValueP ScriptBuildin_##name::eval(Context& ctx) const

/// Return a value from a SCRIPT_FUNCTION
#define SCRIPT_RETURN(value) return to_script(value)

// ----------------------------------------------------------------------------- : Parameters

/// Retrieve a parameter to a SCRIPT_FUNCTION with the given name and type
/** Usage:
 *  @code
 *   SCRIPT_FUNCTION(my_function) {
 *      SCRIPT_PARAM(String, my_string_param);
 *      ... my_string_param ...
 *   }
 *  @endcode
 *  Throws an error if the parameter is not found.
 */
#define SCRIPT_PARAM(Type, name)											\
		SCRIPT_PARAM_N(Type, _(#name), name)
#define SCRIPT_PARAM_N(Type, str, name)										\
		Type name = from_script<Type>(ctx.getVariable(str))

/// Retrieve an optional parameter
/** Usage:
 *  @code
 *   SCRIPT_FUNCTION(my_function) {
 *      SCRIPT_OPTIONAL_PARAM(String, my_string_param) {
 *          ... my_string_param ...
 *      }
 *      ...
 *   }
 *  @endcode
 */
#define SCRIPT_OPTIONAL_PARAM(Type, name)									\
		SCRIPT_OPTIONAL_PARAM_N(Type, _(#name), name)
/// Retrieve a named optional parameter
#define SCRIPT_OPTIONAL_PARAM_N(Type, str, name)							\
		ScriptValueP name##_ = ctx.getVariableOpt(str);						\
		Type name = name##_ ? from_script<Type>(name##_) : Type();			\
		if (name##_)

/// Retrieve an optional parameter, can't be used as an if statement
#define SCRIPT_OPTIONAL_PARAM_(Type, name)									\
		SCRIPT_OPTIONAL_PARAM_N_(Type, _(#name), name)
/// Retrieve a named optional parameter, can't be used as an if statement
#define SCRIPT_OPTIONAL_PARAM_N_(Type, str, name)							\
		ScriptValueP name##_ = ctx.getVariableOpt(str);						\
		Type name = name##_ ? from_script<Type>(name##_) : Type();

/// Retrieve an optional parameter with a default value
#define SCRIPT_PARAM_DEFAULT(Type, name, def)								\
		SCRIPT_PARAM_DEFAULT_N(Type, _(#name), name, def)
/// Retrieve a named optional parameter with a default value
#define SCRIPT_PARAM_DEFAULT_N(Type, str, name, def)						\
		ScriptValueP name##_ = ctx.getVariableOpt(str);						\
		Type name = name##_ ? from_script<Type>(name##_) : def

// ----------------------------------------------------------------------------- : Rules

/// Utility for defining a script rule with a single parameter
#define SCRIPT_RULE_1(funname, type1, name1)								\
        SCRIPT_RULE_1_N(funname, type1, _(#name1), name1)
/// Utility for defining a script rule with a single named parameter
#define SCRIPT_RULE_1_N(funname, type1, str1, name1)						\
	class ScriptRule_##funname: public ScriptValue {						\
	  public:																\
		inline ScriptRule_##funname(const type1& name1) : name1(name1) {}	\
		virtual ScriptType type() const { return SCRIPT_FUNCTION; }			\
		virtual String typeName() const { return _(#funname)_("_rule"); }	\
		virtual ScriptValueP eval(Context& ctx) const;						\
	  private:																\
		type1 name1;														\
	};																		\
	SCRIPT_FUNCTION(funname##_rule) {										\
		SCRIPT_PARAM_N(type1, str1, name1);									\
		return new_intrusive1<ScriptRule_##funname>(name1);					\
	}																		\
	SCRIPT_FUNCTION(funname) {												\
		SCRIPT_PARAM_N(type1, str1, name1);									\
		return ScriptRule_##funname(name1).eval(ctx);						\
	}																		\
	ScriptValueP ScriptRule_##funname::eval(Context& ctx) const

/// Utility for defining a script rule with two parameters
#define SCRIPT_RULE_2(funname, type1, name1, type2, name2)					\
        SCRIPT_RULE_2_N(funname, type1, _(#name1), name1, type2, _(#name2), name2)
/// Utility for defining a script rule with two named parameters
#define SCRIPT_RULE_2_N(funname, type1, str1, name1, type2, str2, name2)	\
	class ScriptRule_##funname: public ScriptValue {						\
	  public:																\
		inline ScriptRule_##funname(const type1& name1, const type2& name2)	\
			: name1(name1), name2(name2) {}									\
		virtual ScriptType type() const { return SCRIPT_FUNCTION; }			\
		virtual String typeName() const { return _(#funname)_("_rule"); }	\
		virtual ScriptValueP eval(Context& ctx) const;						\
	  private:																\
		type1 name1;														\
		type2 name2;														\
	};																		\
	SCRIPT_FUNCTION(funname##_rule) {										\
		SCRIPT_PARAM_N(type1, str1, name1);									\
		SCRIPT_PARAM_N(type2, str2, name2);									\
		return new_intrusive2<ScriptRule_##funname>(name1, name2);			\
	}																		\
	SCRIPT_FUNCTION(funname) {												\
		SCRIPT_PARAM_N(type1, str1, name1);									\
		SCRIPT_PARAM_N(type2, str2, name2);									\
		return ScriptRule_##funname(name1, name2).eval(ctx);				\
	}																		\
	ScriptValueP ScriptRule_##funname::eval(Context& ctx) const


// ----------------------------------------------------------------------------- : EOF
#endif