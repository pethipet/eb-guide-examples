////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Elektrobit Automotive GmbH
// Alle Rechte vorbehalten. All Rights Reserved.
//
// Information contained herein is subject to change without notice.
// Elektrobit retains ownership and all other rights in the software and each
// component thereof.
// Any reproduction of the software or components thereof without the prior
// written permission of Elektrobit is prohibited.
////////////////////////////////////////////////////////////////////////////////

#include <gtf/metainformation/DescriptorProvider.h>
#include <gtf/metainformation/WidgetDescriptor.h>
#include <gtf/typesystem/TypeManager.h>

#include "PreparedStageImpl.h"
#include <gtf/metainformation/PopupStackDescriptor.h>

// pre-defined property types
static const gtf::type::TypeBase    s_typeInt32("int32_t");                              // int32_t property
static const gtf::type::TypeBase    s_typeFloat("float");                                // float property
static const gtf::type::TypeTypedef s_typeColor("color", s_typeInt32);                   // color property. Base type is int32_t
static const gtf::type::TypeBase    s_typeBool("bool", gtf::type::TypeId::eTypeId_bool); // bool property

static gtf::metainformation::PropertyDescriptor BloomEffectWidgetProperties[] =
    {
        gtf::metainformation::PropertyDescriptor(&s_typeColor, "luminosityRGB", "Vector to calculate the realitve luminace threshold for the bright pass filter. Default is (54, 182, 18, 255)", "Common", "54, 182, 18, 255"),

        gtf::metainformation::PropertyDescriptor(&s_typeFloat // property type
            ,
            "threshold" // property name
            ,
            "Regions of the image brighter than this threshold receive blooming" // property description
            ,
            "Common" // property category
            ,
            "1.0"), // default value

        gtf::metainformation::PropertyDescriptor(&s_typeFloat // property type
            ,
            "luminanceBlurPath", "If 1.0, just show the results of the luminance-blur rendering path.", "Common", "0.0"),

        gtf::metainformation::PropertyDescriptor(&s_typeInt32, "blurIterations", "The number of times gaussian blur is applied. Higher numbers improve visual quality. The number of iterations is limited to 20.", "Common", "1")
    };

struct CWidgetDescriptor : public gtf::metainformation::WidgetDescriptor
{
    CWidgetDescriptor(
        const char*                              name_,
        const char*                              alias_,
        const char*                              description_,
        const gtf::metainformation::PropertyDescriptor* properties_,
        uint16_t                                 propertyCount_,
        const char*                              interfaceName_)
    {
        this->m_pName            = name_;
        this->m_pAlias           = alias_;
        this->m_pDescription     = description_;
        this->m_pCategory        = "Custom widgets";
        this->m_pBaseClassName   = "GtfAbstractVisualWidget";
        this->m_fIsAbstract      = false;
        this->m_version          = 0x0100;
        this->m_fIsView          = false;
        this->m_fChildrenAllowed = true;
        this->m_fIsInstantiator  = false;
        this->m_fIsEffect        = false;
        this->m_numProperties    = propertyCount_;
        this->m_pProperties      = properties_;
        this->interfaceName      = interfaceName_;
    }
};

class BloomEffectDescriptorProvider : public gtf::metainformation::DescriptorProvider
{
public:
    virtual gtf::metainformation::ActionDescriptor const* GetActions(uint32_t& count) const
    {
        count = 0;
        return NULL;
    }
    virtual gtf::metainformation::PopupStackDescriptor const* GetPopupStacks(uint32_t& count) const
    {
        count = 0;
        return NULL;
    }
    virtual gtf::metainformation::WidgetDescriptor const* GetWidgets(uint32_t& count) const
    {
        count = 1;
        return &widgetDescriptor;
    }
    virtual gtf::metainformation::WidgetFeatureDescriptor const* GetWidgetFeatures(uint32_t& count) const
    {
        count = 0;
        return NULL;
    }
    virtual gtf::metainformation::ResourceDescriptor const* GetResourceTypes(uint32_t& count) const
    {
        count = 0;
        return NULL;
    }
    virtual bool ResolveTypes(const gtf::typesystem::TypeManager* typeManager)
    {
        bool success = true;

        RESOLVE_PROPERTIES(BloomEffectWidgetProperties);

        return success;
    }

    static const CWidgetDescriptor widgetDescriptor;
};

const CWidgetDescriptor BloomEffectDescriptorProvider::widgetDescriptor(
    BLOOMEFFECT_PLUGIN_NAME,
    "BloomEffect",
    "Fancy effect",
    BloomEffectWidgetProperties,
    ARRAY_SIZE(BloomEffectWidgetProperties),
    NULL);

bloom::PreparedStageImpl::PreparedStageImpl(const gtf::dependencyresolver::DependencyContainerHandle& container_)
    : container(container_)
{
    descriptors = new BloomEffectDescriptorProvider();

    container->registerInstance<gtf::metainformation::DescriptorProvider>(descriptors);
}

bloom::PreparedStageImpl::~PreparedStageImpl()
{
    container->unregisterInstance(descriptors);
}
