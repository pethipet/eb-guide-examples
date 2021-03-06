﻿////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Elektrobit Automotive GmbH
// Alle Rechte vorbehalten. All Rights Reserved.
//
// Information contained herein is subject to change without notice.
// Elektrobit retains ownership and all other rights in the software and each
// component thereof.
// Any reproduction of the software or components thereof without the prior
// written permission of Elektrobit is prohibited.
////////////////////////////////////////////////////////////////////////////////


namespace AnnotationsServicePlugin.Service
{
    using System;

    using AnnotationsServicePlugin.Model;

    using Elektrobit.Guide.Studio.Model.Elements;
    using Elektrobit.Guide.Studio.Model.Session;

    public interface IAnnotationService
    {
        /// <summary>
        /// Returns the annotation entry for the passed element.
        /// May return <c>null</c> if there is no annotation present.
        /// </summary>
        IAnnotationData GetAnnotation(
            IProjectContext projectContext,
            IModelElement element);

        /// <summary>
        /// Creates or updates the annotation for the passed element.
        /// </summary>
        IAnnotationData SetAnnotation(
            IWriteSession session,
            IProjectContext projectContext,
            IModelElement element,
            string annotation);

        /// <summary>
        /// Deletes the annotation for the passed element.
        /// Does nothing if there is no annotation for the element.
        /// </summary>
        void DeleteAnnotation(
            IWriteSession session,
            IProjectContext projectContext,
            IModelElement element);

        /// <summary>
        /// Returns an observable that publishes the value of the annotation for
        /// the passed element. The observable publishes <see cref="string.Empty"/>
        /// if there is no annotation for the passed element.
        /// </summary>
        IObservable<string> ObserveAnnotation(
            IProjectContext projectContext,
            IModelElement element);
    }
}
