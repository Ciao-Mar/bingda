define laser ranger
(
  sensor
  (
    range_max 8.0
    fov 360.0
    samples 1000
  )
  # generic model properties
  color "black"
  size [ 0.06 0.15 0.03 ]
)

define robot position
(
  pose [ 0.0 0.0 0.0 0.0 ]

  odom_error [0.03 0.03 999999 999999 999999 0.01]

  size [ 0.2 0.2 0.40 ]
  origin [ 0.0 0.0 0.0 0.0 ]
  gui_nose 1
  drive "diff"
  color "red"
  
  # spawn sensors
  laser(pose [ 0.0515 0.0 -0.11 0.0 ])
)
