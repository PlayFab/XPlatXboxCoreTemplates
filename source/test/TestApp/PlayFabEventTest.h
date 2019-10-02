// Copyright (C) Microsoft Corporation. All rights reserved.

#pragma once

#include <functional>
#include <string>
#include <playfab/PlayFabEventApi.h>
#include "TestCase.h"

namespace PlayFab
{
    struct PlayFabError;

    namespace EventsModels
    {
        struct TelemetryIngestionConfigResponse;
        struct WriteEventsResponse;
    }
}

namespace PlayFabUnit
{
    struct TestContext;

    class PlayFabEventTest : public TestCase
    {
        private:
            /// QoS API
            void QosResultApi(TestContext& testContext);

            /// EVENTS API
            /// Test that sends heavyweight events as a whole batch.
            void EventsApi(TestContext& testContext);
            void OnEventsApiSucceeded(const PlayFab::EventsModels::WriteEventsResponse&, void* customData);
            void OnEventsApiFailed(const PlayFab::PlayFabError& error, void* customData);

            /// EVENTS API
            /// PlayFab heavyweight events (emitted individually
            ///   and processed in a background thread using event pipeline (router, batching, etc))
            void HeavyweightEvents(TestContext& testContext);

            /// EVENTS API
            /// Non-PlayStream, lightweight events (emitted individually
            ///   and processed in a background thread using event pipeline (router, batching, etc))
            void LightweightEvents(TestContext& testContext);

            void LambdaCallbackTest(TestContext& testContext);
            void PrivateMemberCallbackTest(TestContext& testContext);

            // State
            bool loggedIn;
            std::shared_ptr<PlayFab::PlayFabEventAPI*> eventApi;
            static std::shared_ptr<TestContext*> eventTestContext;
            static const int eventEmitCount = 6;
            static size_t eventBatchMax;
            static int eventPassCount;
            static int eventFailCount;
            static std::string eventFailLog;

            // Utility
            void EmitEventsWithCallback(PlayFab::PlayFabEventType eventType, std::function<void(std::shared_ptr<const PlayFab::IPlayFabEmitEventRequest>, std::shared_ptr<const PlayFab::IPlayFabEmitEventResponse>)> callback);
            void EmitEvents(PlayFab::PlayFabEventType eventType);
            static void EmitEventCallback(std::shared_ptr<const PlayFab::IPlayFabEvent> event, std::shared_ptr<const PlayFab::IPlayFabEmitEventResponse> response);
            void NonStaticEmitEventCallback(std::shared_ptr<const PlayFab::IPlayFabEvent> event, std::shared_ptr<const PlayFab::IPlayFabEmitEventResponse> response);

            template<typename T> std::function<void(const T&, void*)> Callback(void(PlayFabEventTest::*func)(const T&, void*))
            {
                return std::bind(func, this, std::placeholders::_1, std::placeholders::_2);
            }

        protected:
            void AddTests() override;

        public:
            void ClassSetUp() override;
            void SetUp(TestContext& /*testContext*/) override;
            void Tick(TestContext& testContext) override;
            void TearDown(TestContext& /*testContext*/) override;
            void ClassTearDown() override;
    };
}