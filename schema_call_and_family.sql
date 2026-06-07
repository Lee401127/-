-- 家属与老人绑定、呼叫记录（执行一次）
-- 请根据实际库名： USE your_database;

CREATE TABLE IF NOT EXISTS family_elder (
  id INT AUTO_INCREMENT PRIMARY KEY,
  family_user_id INT NOT NULL,
  elder_user_id INT NOT NULL,
  created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  UNIQUE KEY uk_family_elder (family_user_id, elder_user_id),
  KEY idx_family (family_user_id),
  KEY idx_elder (elder_user_id),
  CONSTRAINT fk_fe_family FOREIGN KEY (family_user_id) REFERENCES user(user_id),
  CONSTRAINT fk_fe_elder FOREIGN KEY (elder_user_id) REFERENCES user(user_id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

CREATE TABLE IF NOT EXISTS call_record (
  call_id INT AUTO_INCREMENT PRIMARY KEY,
  elder_user_id INT NOT NULL,
  call_type INT NOT NULL DEFAULT 0 COMMENT '0普通 1紧急',
  call_time DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
  remark VARCHAR(255) DEFAULT '',
  KEY idx_elder_time (elder_user_id, call_time),
  CONSTRAINT fk_cr_elder FOREIGN KEY (elder_user_id) REFERENCES user(user_id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- call_record.elder_user_id、family_elder 两端均为 user.user_id，与独立的 elder 表无关；若代码已不再写入 elder 表，可 DROP elder。
--
-- 示例：将已存在的家属用户与老人用户绑定（请替换为真实 user_id 或用手机号子查询）
-- INSERT INTO family_elder (family_user_id, elder_user_id)
-- SELECT f.user_id, e.user_id FROM user f, user e
-- WHERE f.user_phone = '13900000001' AND e.user_phone = '13900000002'
-- LIMIT 1;
