#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>

int
main (int argc, char** argv)
{
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZ>);

  // Fill in the cloud data
  pcl::PCDReader reader;
  // Replace the path below with the path where you saved your file
  reader.read<pcl::PointXYZ> ("My_scene_filtered_inliers.pcd", *cloud);

  std::cerr << "Cloud before filtering: " << std::endl;
  std::cerr << *cloud << std::endl;

  // Create the filtering object
  pcl::PassThrough<pcl::PointXYZ> pass;
  pass.setInputCloud (cloud);
  pass.setFilterFieldName ("x");
  pass.setFilterLimits (0.0, 1.5);
  //pass.setFilterLimitsNegative (true);
  pass.filter (*cloud_filtered);

  std::cerr << "Cloud after pass through filtering: " << std::endl;
  std::cerr << *cloud_filtered << std::endl;

  pcl::PCDWriter writer;
  writer.write<pcl::PointXYZ> ("My_scene_passthroughfiltered_inliers.pcd", *cloud_filtered, false);

  pass.setFilterLimitsNegative (true);
  pass.filter (*cloud_filtered);
  writer.write<pcl::PointXYZ> ("My_scene_passthroughfiltered_outliers.pcd", *cloud_filtered, false);

  return (0);
}