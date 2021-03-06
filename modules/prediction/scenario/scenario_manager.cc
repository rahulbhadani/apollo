/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#include "modules/prediction/scenario/scenario_manager.h"

#include <algorithm>

#include "modules/prediction/common/prediction_gflags.h"
#include "modules/prediction/scenario/prioritization/obstacles_prioritizer.h"
#include "modules/prediction/scenario/right_of_way/right_of_way.h"

namespace apollo {
namespace prediction {

using apollo::perception::PerceptionObstacle;
using common::adapter::AdapterConfig;
using common::math::Box2d;
using common::math::Vec2d;

ScenarioManager::ScenarioManager() {}

void ScenarioManager::Run() {
  auto environment_features = FeatureExtractor::ExtractEnvironmentFeatures();

  auto ptr_scenario_features = ScenarioAnalyzer::Analyze(environment_features);

  current_scenario_ = ptr_scenario_features->scenario();

  if (FLAGS_enable_prioritize_obstacles) {
    ObstaclesPrioritizer::PrioritizeObstacles(environment_features,
                                              ptr_scenario_features);
  }
  // TODO(all) other functionalities including lane, junction filters
}

void ScenarioManager::AssignRightOfWay() { RightOfWay::Analyze(); }

const Scenario& ScenarioManager::scenario() const { return current_scenario_; }

}  // namespace prediction
}  // namespace apollo
