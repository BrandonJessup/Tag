# Database Design
## Tables
#### File
| Field     | Type                      | Description                 |
| --------- | ------------------------- | --------------------------- |
| FileId    | auto incrementing integer | primary key                 |
| TypeId    | integer                   | foreign key from type table |
| Name      | varchar(255)              | filename without extension  |
| Path      | varchar(255) unique       | complete file path          |
| Thumbnail | varchar(255) unique       | relative path to thumbnail  |

#### Type
| Field  | Type                      | Description  |
| ------ | ------------------------- | ------------ |
| TypeId | auto incrementing integer | primary key  |
| Name   | varchar(255) unique       | type of file |

#### Tag
| Field     | Type                      | Description                         |
| --------- | ------------------------- | ----------------------------------- |
| TagId     | auto incrementing integer | primary key                         |
| Name      | varchar(255) unique       | name the tag will be displayed with |
| IsSpecial | integer(1) default 0      | whether the tag can be deleted      |

#### FileTag
| Field  | Type    | Description                 |
| ------ | ------- | --------------------------- |
| FileId | integer | foreign key from file table |
| TagId  | integer | foreign key from tag table  |
