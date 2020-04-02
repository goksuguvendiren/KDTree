//
// Created by goksu on 3/30/20.
//

#include "kd_tree.hpp"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/spdlog.h>

int main()
{
    auto logger = spdlog::basic_logger_mt("basic_logger", "../logs/today.txt");
    spdlog::set_default_logger(logger);
    logger->set_level(spdlog::level::info);
    logger->flush_on(spdlog::level::info);

    spdlog::set_default_logger(logger);
    logger->info("Starting KDTree");
    spdlog::flush_every(std::chrono::seconds(1));
    spdlog::set_level(spdlog::level::trace);

    kd_tree::tree<glm::vec1> tree(std::vector<glm::vec1>{glm::vec1{1}, glm::vec1{2}, glm::vec1{5}, glm::vec1{3}, glm::vec1{0}});

    return 0;
}