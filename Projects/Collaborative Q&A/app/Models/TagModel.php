<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class TagModel extends Model
{
    protected $table = 'tags';
    public $timestamps = false;

    public function questions()
    {
        return $this->belongsToMany(QuestionModel::class, 'questiontag', 'tagid', 'questionid');
    }
}
