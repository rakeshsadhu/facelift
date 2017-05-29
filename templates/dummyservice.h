
{% set class = '{0}'.format(interface) %}

/****************************************************************************
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
****************************************************************************/

#pragma once

#include "{{interface|fullyQualifiedPath}}PropertyAdapter.h"
#include "dummy/DummyModel.h"

{{module|namespaceOpen}}

/**
 * Dummy implementation of the {{class}} API
 */
class {{class}}Dummy : public {{class}}PropertyAdapter {

    Q_OBJECT

public:
    {{class}}Dummy(QObject* parent = nullptr): {{class}}PropertyAdapter(parent), m_dummy(*this) {
        setImplementationID("Dummy");
    }

    {% for operation in interface.operations %}
    {{operation|returnType}} {{operation}}(
            {% set comma = joiner(",") %}
            {% for parameter in operation.parameters %}
            {{ comma() }}
            {{parameter|returnType}} {{parameter.name}}
            {% endfor %}
) override {

        m_dummy.logMethodCall("{{operation}}"
                {% for parameter in operation.parameters %}

                 , {{parameter.name}}
                {% endfor %}
        );
    }
    {% endfor %}

    {% for property in interface.properties %}
    	{% if (not property.readonly) %}
    void set{{property}}(const {{property|returnType}}& newValue) override {
    	m_dummy.logSetterCall("{{property}}", newValue);
    	m_{{property}} = newValue;
    }
        {% endif %}
    {% endfor %}



    class Dummy : public DummyModel<{{class}}> {

    public:
        Dummy({{class}}PropertyAdapter& adapter) : DummyModel<{{class}}>(&adapter), m_adapter(adapter) {
            init();
            {% for property in interface.properties %}
            initWidget(m_adapter.m_{{property.name}}, "{{property.name}}");
            {% endfor %}

            {% for event in interface.signals %}
            initSignal<
			            {% set comma = joiner(",") %}
			            {% for parameter in event.parameters %}
			            {{ comma() }}
			            {{parameter|returnType}}
			            {% endfor %}
			    >("{{event.name}}", {
			            {% set comma = joiner(",") %}
			            {% for parameter in event.parameters %}
			            {{ comma() }}
			            "{{parameter}}"
			            {% endfor %}
			    }, &{{class}}::{{event.name}});

            {% endfor %}

            finishInit();
        }

		void writeJsonValues(QJsonObject& jsonObject) const override {
			Q_UNUSED(jsonObject);
			{% for property in interface.properties %}
			writeJSONProperty(jsonObject, m_adapter.m_{{property.name}}, "{{property.name}}");
			{% endfor %}
		}

		void loadJsonValues(const QJsonObject& jsonObject) override {
			Q_UNUSED(jsonObject);
			{% for property in interface.properties %}
			readJSONProperty(jsonObject, m_adapter.m_{{property.name}}, "{{property.name}}");
			{% endfor %}
		}

		{{class}}PropertyAdapter& m_adapter;

    };

    private:
        Dummy m_dummy;

};

{{module|namespaceClose}}

