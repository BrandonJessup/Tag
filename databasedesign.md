# Database Design
## Tables
#### File
| Field     | Type                               | Description                |
| --------- | ---------------------------------- | -------------------------- |
| FileId    | auto incrementing integer          | primary key                |
| Name      | varchar(255)                       | filename without extension |
| Extension | varchar(255)                       | file extension             |
| Filepath  | varchar(255)                       | complete filepath          |

#### Tag
| Field | Type                      | Description                         |
| ----- | ------------------------- | ----------------------------------- |
| TagId | auto incrementing integer | primary key                         |
| Name  | varchar(255)              | name the tag will be displayed with |

#### FileTag
| Field  | Type    | Description                 |
| ------ | ------- | --------------------------- |
| FileId | integer | foreign key from file table |
| TagId  | integer | foreign key from tag table  |
