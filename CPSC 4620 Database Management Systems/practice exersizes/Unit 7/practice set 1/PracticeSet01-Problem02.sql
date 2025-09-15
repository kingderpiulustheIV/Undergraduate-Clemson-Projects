-- ## Problem 2:
-- 
-- In addition, Channel Development team requires the channels which have commission 
-- rates higher than 10%.  
-- 
-- +---------------+-------------------+
-- |  ChannelName  | ChannelCommission |
-- +---------------+-------------------+
-- |  Online Ads   |       0.15        |
-- | Travel Agency |       0.13        |
-- +---------------+-------------------+

/* YOUR SOLUTION HERE */
SELECT ChannelName, ChannelCommission
FROM CHANNEL
WHERE ChannelCommission > 0.10;